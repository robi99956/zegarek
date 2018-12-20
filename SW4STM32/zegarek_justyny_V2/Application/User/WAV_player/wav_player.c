/*
 * wav_player.c
 *
 *  Created on: 27 paü 2018
 *      Author: Robert
 */
#include <stdlib.h>
#include <string.h>

#include "stm32f0xx_hal.h"
#include "fatfs.h"

#include "wav_player.h"

#define DAC_BUFF_SIZE 1024
#define DAC_BUFF_HALF_SIZE (DAC_BUFF_SIZE/2)
#define DAC_SUB_BUFFER_SIZE 64
uint16_t dac_buf[2][DAC_BUFF_HALF_SIZE];

wav_info_t wav_info;

static TIM_HandleTypeDef * timer;
static DAC_HandleTypeDef * dac_handle;
static uint32_t channel;
static void * conversion_buf;

extern UART_HandleTypeDef huart2;
void uart_debug( char * str )
{
	HAL_UART_Transmit(&huart2, (uint8_t*)str, strlen(str), 100);
}

void uart_debug_int( char * desc, int x )
{
	char str[20];
	itoa(x, str, 10);
	uart_debug(desc);
	uart_debug(str);
	uart_debug("\r\n");
}

void wav_player_register_hardware( DAC_HandleTypeDef * handle, uint32_t _channel, TIM_HandleTypeDef * _timer )
{
	dac_handle = handle;
	channel = _channel;
	timer = _timer;
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

	res |= f_lseek(file, 20);
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
	if( info->shift_bits < 0 ) info->shift_bits *= -1;

	uart_debug_int("shift: ",info->shift_bits);
	uart_debug_int("res: ", info->resolution);

	return (res==FR_OK);
}

uint8_t get_wav_data_8( uint16_t * dst, uint8_t * buf8, uint16_t len )
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
		dst[i] = ((uint16_t)buf8[j]) << (12 - src_resolution);
		j += wav_info.num_channels;
	}

	return br;
}

uint8_t get_wav_data_16( uint16_t * dst, uint16_t * buf16, uint16_t len )
{
	if( buf16 == NULL ) return 0;

	UINT br;
	FRESULT res;
	res = f_read(&USERFile, buf16, len*2, &br);

	if( (res != FR_OK) || (br != len*2) ) return 0;

	int8_t shift = wav_info.shift_bits;
	uint8_t src_resolution = wav_info.resolution;

	if( src_resolution > 12)
		for( uint16_t i=0; i<len; i++ )
		{
			dst[i] = ((uint16_t)buf16[i]) >> shift;
		}
	else
		for( uint16_t i=0; i<len; i++ )
		{
			dst[i] = ((uint16_t)buf16[i]) << shift;
		}

	return br/2;
}

uint8_t get_wav_data_32( uint16_t * dst, uint32_t * buf32, uint16_t len )
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

	return br/4;
}

uint8_t get_wav_data( uint16_t * dst, uint16_t len )
{
	uint8_t src_resolution = wav_info.resolution;

	if( src_resolution > 32 || src_resolution == 0 ) return 0;

	if( src_resolution <= 8 ) return get_wav_data_8(dst, (uint8_t*)conversion_buf, len);
	if( src_resolution > 8 && src_resolution <= 16 ) return get_wav_data_16(dst, (uint16_t*)conversion_buf, len);

	return get_wav_data_32(dst, (uint32_t*)conversion_buf, len);
}

uint8_t fill_buffer( uint8_t section )
{
	uint16_t * dst = dac_buf[section];
	uint16_t got_samples_all=0, got_samples_current=0;

	while( got_samples_all < DAC_BUFF_HALF_SIZE )
	{
		got_samples_current = get_wav_data(dst+got_samples_all, DAC_SUB_BUFFER_SIZE);

		if( got_samples_current == 0 )
		{
			HAL_DAC_Stop_DMA(dac_handle, channel);
			HAL_TIM_Base_Stop(timer);

			free(conversion_buf);
			f_close(&USERFile);

			return 0;
		}

		got_samples_all += got_samples_current;
	}

	return 1;
}

void HAL_DACEx_ConvCpltCallbackCh2(DAC_HandleTypeDef* hdac)
{
	if( hdac->Instance != dac_handle->Instance ) return;

	fill_buffer(1);
}

void HAL_DACEx_ConvHalfCpltCallbackCh2(DAC_HandleTypeDef* hdac)
{
	if( hdac->Instance != dac_handle->Instance ) return;

	fill_buffer(0);
}

static void set_timer_frequency( uint32_t sample_rate )
{
	uint32_t core_freq = HAL_RCC_GetHCLKFreq();

	uint32_t arr = core_freq/sample_rate;

	timer->Instance->ARR = arr;
}

static uint8_t allocate_subbuf( uint16_t resolution )
{
	uint16_t size = DAC_SUB_BUFFER_SIZE*( resolution/8 + ((resolution%8)?1:0) );

	conversion_buf = malloc(size);

	if( conversion_buf == NULL ) return 0;

	return 1;
}

void wav_player_start( char * filename )
{
	FRESULT res;

	res = f_open(&USERFile, filename, FA_READ | FA_OPEN_EXISTING);
	if( res != FR_OK ) return;

	if( get_wav_info(&USERFile, &wav_info) == 0 ) return;

	if( allocate_subbuf(wav_info.resolution) == 0 ) return;

	if( fill_buffer(0) == 0 ) return;
	if( fill_buffer(1) == 0 ) return;

	set_timer_frequency(wav_info.sample_rate);

	HAL_TIM_Base_Start(timer);
	HAL_DAC_Start(dac_handle, channel);
	HAL_DAC_Start_DMA(dac_handle, channel, (uint32_t*)dac_buf[0], DAC_BUFF_SIZE, DAC_ALIGN_12B_R);
}
