/*
 * wav_player.c
 *
 *  Created on: 27 paŸ 2018
 *      Author: Robert
 */

#include "stm32f0xx_hal.h"
#include "fatfs.h"

#include "wav_player.h"

#define DAC_BUFF_SIZE 512
#define DAC_BUFF_HALF_SIZE (DAC_BUFF_SIZE/2)
#define DAC_SUB_BUFFER_SIZE 64
uint32_t dac_buf[2][DAC_BUFF_HALF_SIZE];

wav_info_t wav_info;

static DAC_HandleTypeDef * dac_handle;
static uint32_t channel;
static void * conversion_buf;

void wav_player_register_dac( DAC_HandleTypeDef * handle, uint32_t _channel )
{
	dac_handle = handle;
	channel = _channel;
}

uint8_t check_wav_valid(FIL * file)
{
	byte_field_32b_t buf;
	UINT br;
	FRESULT res = 0;

	res |= f_lseek(file, 0);
	res |= f_read(file, &buf, 4, &br);

	if( buf.all != RIFF_U32 || res != FR_OK ) return 0; // napis RIFF

	res |= f_lseek(file, 8);
	res |= f_read(file, &buf, 4, &br);

	if( buf.all != WAVE_U32 || res != FR_OK ) return 0; // napis WAVE

	res |= f_lseek(file, 16);
	res |= f_read(file, &buf, 4, &br);

	if( buf.all != 16 || res != FR_OK ) return 0; // rozmiar sekcji informacyjnej w PCM to 16

	res |= f_read(file, &buf.words[0], 2, &br);

	if( buf.words[0] != 1 || res != FR_OK ) return 0; // kodowanie PCM - brak kompresji

	return 1;
}

uint8_t get_wav_info(FIL * file, wav_info_t * info)
{
	if( check_wav_valid(file) == 0 ) return 0;

	UINT br;
	FRESULT res = 0;

	res |= f_read(file, &info->num_channels, 2, &br);
	res |= f_read(file, &info->sample_rate, 4, &br);
	res |= f_lseek(file, 34);
	res |= f_read(file, &info->resolution, 2, &br);

	info->shift_bits = 12-info->resolution;

	return (res==FR_OK);
}

uint8_t get_wav_data_8( uint32_t * dst, uint8_t * buf8, uint16_t len )
{
	if( buf8 == NULL ) return 0;

	UINT br;
	FRESULT res;
	res = f_read(&USERFile, buf8, len, &br);

	if( res != FR_OK || br != len ) return 0;

	uint8_t src_resolution = wav_info.resolution;

	uint16_t j=0;

	for( uint16_t i=0; i<len; i++ )
	{
		dst[i] = ((uint32_t)buf8[j]) << (12 - src_resolution);
		j += wav_info.num_channels;
	}

	return 1;
}

uint8_t get_wav_data_16( uint32_t * dst, uint16_t * buf16, uint16_t len )
{
	if( buf16 == NULL ) return 0;

	UINT br;
	FRESULT res;
	res = f_read(&USERFile, buf16, len*2, &br);

	if( res != FR_OK || br != len ) return 0;

	uint8_t src_resolution = wav_info.resolution;

	if( src_resolution > 12)
		for( uint16_t i=0; i<len; i++ )
		{
			dst[i] = ((uint16_t)buf16[i]) >> (src_resolution-12);
		}
	else
		for( uint16_t i=0; i<len; i++ )
		{
			dst[i] = ((uint32_t)buf16[i]) << (12-src_resolution);
		}

	return 1;
}

uint8_t get_wav_data_32( uint32_t * dst, uint32_t * buf32, uint16_t len )
{
	if( buf32 == NULL ) return 0;

	UINT br;
	FRESULT res;
	res = f_read(&USERFile, buf32, len*4, &br);

	if( res != FR_OK || br != len ) return 0;

	uint8_t src_resolution = wav_info.resolution;

	for( uint16_t i=0; i<len; i++ )
	{
		dst[i] = (uint32_t)(buf32[i] >> ( src_resolution - 12 ));
	}

	return 1;
}

uint8_t get_wav_data( uint32_t * dst, uint16_t len )
{
	uint8_t src_resolution = wav_info.resolution;
	if( src_resolution > 32 || src_resolution == 0 ) return 0;

	if( src_resolution <= 8 ) return get_wav_data_8(dst, (uint8_t*)conversion_buf, len);
	if( src_resolution > 8 && src_resolution <= 16 ) return get_wav_data_16(dst, (uint16_t*)conversion_buf, len);

	return get_wav_data_32(dst, (uint32_t*)conversion_buf, len);
}

uint8_t fill_buffer( uint8_t section )
{
	uint32_t * dst = dac_buf[section];
	uint16_t got_samples_all=0, got_samples_current=0;

	while( got_samples_all < DAC_BUFF_HALF_SIZE )
	{
		got_samples_current = get_wav_data(dst, DAC_SUB_BUFFER_SIZE);

		if( got_samples_current == 0 )
		{
			HAL_DAC_Stop_DMA(dac_handle, channel);
			return 0;
		}

		dst += got_samples_current;
		got_samples_all += got_samples_current;
	}

	return 1;
}

void HAL_DACEx_ConvCpltCallbackCh2(DAC_HandleTypeDef* hdac)
{
	UNUSED(hdac);
	fill_buffer(1);
}

void HAL_DACEx_ConvHalfCpltCallbackCh2(DAC_HandleTypeDef* hdac)
{
	UNUSED(hdac);
	fill_buffer(0);
}

void wav_player_start( char * filename )
{
	FRESULT res;

	res = f_open(&USERFile, filename, FA_READ | FA_OPEN_EXISTING);
	if( res != FR_OK ) return;

	get_wav_info(&USERFile, &wav_info);

	if( fill_buffer(0) == 0 ) return;
	if( fill_buffer(1) == 0 ) return;

	HAL_DAC_Start_DMA(dac_handle, channel, &dac_buf[0], DAC_BUFF_SIZE, DAC_ALIGN_12B_R);
}
