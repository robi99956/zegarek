/*
 * wav_player.h
 *
 *  Created on: 27 paü 2018
 *      Author: Robert
 */

#ifndef APPLICATION_USER_WAV_PLAYER_WAV_PLAYER_H_
#define APPLICATION_USER_WAV_PLAYER_WAV_PLAYER_H_

typedef struct _wav_info
{
	uint16_t num_channels;
	uint32_t sample_rate;
	uint16_t resolution;
	int8_t shift_bits;
} wav_info_t;

typedef	union _byte_field_32b
{
	uint32_t all;
	uint16_t words[2];
	uint8_t bytes[4];
} byte_field_32b_t;

#define RIFF_U32 0x46464952
#define WAVE_U32 0x45564157

#endif /* APPLICATION_USER_WAV_PLAYER_WAV_PLAYER_H_ */
