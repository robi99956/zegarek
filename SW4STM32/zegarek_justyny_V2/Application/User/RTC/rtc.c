/*
 * rtc.c
 *
 *  Created on: 28 wrz 2018
 *      Author: Robert
 */

#include "stm32f0xx_hal.h"
#include "rtc.h"
#include "../Scheduler/scheduler.h"
#include "../WiFi/wifi.h"

CZAS time_struct;

uint8_t get_time_callback( void )
{
	scheduler_unlock(REQUIRES_UART_ANSWER);
	return 1;
}

void get_time_task( void )
{
	static const char cmd[] = "TIME\r";

	wifi_uart_callback_register(get_time_callback);
	wifi_uart_puts(cmd);
}

void rtc_module_init( void )
{
	scheduler_add_task(get_time_task, 15, DELAY_SECONDS, REQUIRES_UART_ANSWER | REPEATABLE);
}


