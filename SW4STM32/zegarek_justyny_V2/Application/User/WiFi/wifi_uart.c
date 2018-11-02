/*
 * wifi_uart.c
 *
 *  Created on: 21 wrz 2018
 *      Author: Robert
 */
#include <string.h>
#include <stdlib.h>

#include "wifi.h"
#include "../Scheduler/scheduler.h"

UART_HandleTypeDef * uart_handle;

wifi_uart_callback callback;

#define STD_LEN 200

char rec_buf[STD_LEN+1];

uint8_t get_wifi_buffer( char ** buf )
{
	*buf = rec_buf;
	return sizeof(rec_buf);
}

void wifi_uart_handle_register( UART_HandleTypeDef * huart )
{
	uart_handle = huart;
}

void wifi_uart_callback_register( wifi_uart_callback _callback )
{
	callback = _callback;
}

void wifi_uart_init( void )
{
	HAL_UART_Init(uart_handle);
}

void wifi_uart_deinit( void )
{
	HAL_UART_DeInit(uart_handle);
}

void wifi_uart_puts( const char * s )
{
	uint16_t len = strlen(s);

	HAL_UART_Transmit(uart_handle, (uint8_t*)s, len, 128);
}

void wifi_uart_put_buf( const uint8_t * data, uint16_t len )
{
	HAL_UART_Transmit(uart_handle, (uint8_t*)data, len, 128);
}

void wifi_uart_putint( int val, uint8_t base )
{
	char buf[30];
	itoa(val, buf, base);

	wifi_uart_puts(buf);
}

void wifi_uart_send_space( void )
{
	wifi_uart_puts(" ");
}

void wifi_uart_send_CR( void )
{
	wifi_uart_puts("\r");
}

void wifi_uart_send_code( char * name, uint8_t code )
{
	wifi_uart_puts(name);
	wifi_uart_send_space();
	wifi_uart_putint(code, 10);
	wifi_uart_puts("\r\n");
}

void wifi_uart_start_rec( void )
{
	HAL_UART_Receive_DMA(uart_handle, (uint8_t*)rec_buf, STD_LEN);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if( callback ) callback(rec_buf);

	memset(rec_buf, 0, STD_LEN);
	wifi_uart_start_rec();
}
