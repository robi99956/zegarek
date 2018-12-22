/*
 * led.c
 *
 *  Created on: 11 gru 2018
 *      Author: Robert
 */

#include "stm32f0xx_hal.h"

#include <string.h>

#include "led.h"
#include "../RTC/rtc.h"
#include "../Scheduler/scheduler.h"

static TIM_HandleTypeDef * timer;
static SPI_HandleTypeDef * spi;
static GPIO_TypeDef * LATCH_gpio;
static uint16_t LATCH_pin;

static uint8_t cyfry[4];
static uint8_t control;

static LED_mode_t mode = LED_TIME;

static const uint8_t data[] = {
	0xDD,	// 0
	0x05,	// 1
	0xB9,	// 2
	0xAD,	// 3
	0x65,	// 4
	0xEC,	// 5
	0xFC,	// 6
	0xC5,	// 7
	0xFD,	// 8
	0xED,	// 9
	0xF5,	// 10  A
	0x7C,	// 11  b
	0xD8,	// 12  C
	0x3D,	// 13  d
	0xF8,	// 14  E
	0xF0,	// 15  F
};

#define LED_DOT 0x02

void led_init( TIM_HandleTypeDef * htim, SPI_HandleTypeDef * hspi, GPIO_TypeDef * L_gpio, uint16_t L_pin )
{
	timer = htim;
	spi = hspi;
	LATCH_gpio = L_gpio;
	LATCH_pin = L_pin;

	timer->Instance->ARR = 210;

	HAL_TIM_Base_Start_IT(timer);
}



void led_set_1( uint16_t val )
{
	cyfry[0] = data[val/1000];
	cyfry[1] = data[(val%1000)/100];
	cyfry[2] = data[(val%100)/10];
	cyfry[3] = data[val%10];
}

void led_set_2( uint8_t val1, uint8_t val2 )
{
	cyfry[0] = data[(val1%100)/10];
	cyfry[1] = data[val1%10];
	cyfry[2] = data[(val2%100)/10];
	cyfry[3] = data[val2%10];
}

void led_set_4( uint8_t c1, uint8_t c2, uint8_t c3, uint8_t c4 )
{
	cyfry[0] = data[c1];
	cyfry[1] = data[c2];
	cyfry[2] = data[c3];
	cyfry[3] = data[c4];
}

void led_dot( uint8_t nr, uint8_t on_off )
{
	if( on_off ) cyfry[nr] |= LED_DOT;
	else cyfry[nr] &= ~LED_DOT;
}

void led_show_time( RTC_TimeTypeDef * time )
{
	if( mode != LED_TIME ) return;

	led_set_2(time->Hours, time->Minutes);
}

void led_show_error( uint8_t error )
{
	if( mode != LED_ERROR ) return;

	led_set_4(0x0E, error/100, (error%100)/10, error%10);
	mode = LED_ERROR_LOCK;
}

void led_clear_ip_task( task_handle_t task )
{
	UNUSED(task);

	led_set_mode(LED_TIME);
}

void led_show_ip( char * ip )
{
	if( mode != LED_IP ) return;

	uint8_t idx = strlen(ip)-1;

	uint8_t c4 = ip[idx]-'0';
	uint8_t c3 = ip[idx-1]-'0';
	uint8_t c2 = ip[idx-2]-'0';
	uint8_t c1 = ip[idx-4]-'0';

	led_set_4(c1, c2, c3, c4);
	led_dot(0, 1);

	scheduler_add_task(led_clear_ip_task, 5, DELAY_SECONDS, 0, NULL);
}

void led_set_mode( LED_mode_t _mode )
{
	if( mode != LED_ERROR_LOCK ) mode = _mode;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if( htim != timer ) return;

	static uint8_t cyfra;

	control &= ~0x7f;
	control |= (1<<(cyfra+1));

	uint8_t buf[2];
	buf[0] = control;
	buf[1] = cyfry[cyfra];

	HAL_SPI_Transmit(spi, buf, 2, 100);

	HAL_GPIO_WritePin(LATCH_gpio, LATCH_pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LATCH_gpio, LATCH_pin, GPIO_PIN_RESET);

	cyfra++;
	if( cyfra == 4 ) cyfra = 0;
}

