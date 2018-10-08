/*
 * wifi.h
 *
 *  Created on: 21 wrz 2018
 *      Author: Robert
 */

#ifndef APPLICATION_USER_WIFI_WIFI_H_
#define APPLICATION_USER_WIFI_WIFI_H_

#include "stm32f0xx_hal.h"

typedef enum _get_time_mode{ MANUAL, NTP, API_TIME, API_LOCTIME } get_time_mode;
typedef enum _server_callback_type{ RX_CALLBACK, TX_CALLBACK } server_callback_type;

typedef union _IP_t
{
	uint8_t bytes[4]; // 0 - najbardziej z lewej, 3 - najbardziej z prawej
	uint32_t all;
} IP_t;


typedef struct _NTP_info
{
	char ip[20];
} NTP_info;

typedef struct _TIME_API_info
{
	char url[200];
	char marker[20];
} TIME_API_info;

typedef struct _LOC_API_info
{
	char url[200];
	char marker_lon[20];
	char marker_lat[20];
} LOC_API_info;

typedef struct _CONNECT_info
{
	char ssid[100];
	char passwd[100];
} CONNECT_info;

typedef struct _WiFi_config_t
{
	get_time_mode mode;
	int8_t gmt_offset;
	uint8_t use_summerwinter_time;

	NTP_info ntp_info;

	TIME_API_info time_api_info;

	LOC_API_info loc_api_info;

	CONNECT_info connect_info;

	char time_format[24];

	char country_code[8];

} WiFi_config_t;

typedef struct _wifi_string
{
	char * s;
	uint16_t len;
} wifi_string;

typedef void(*config_fun)(WiFi_config_t*);
typedef uint8_t(*wifi_uart_callback)(char*);

void wifi_uart_handle_register( UART_HandleTypeDef * huart );
void wifi_uart_callback_register( wifi_uart_callback _callback );
void wifi_uart_server_callback_register( wifi_uart_callback _callback, server_callback_type type );
void wifi_uart_start_rec( void );

void wifi_uart_init( void );
void wifi_uart_deinit( void );

void wifi_uart_puts( const char * s );
void wifi_uart_putint( int val, uint8_t base );
void wifi_uart_send_space( void );
void wifi_uart_send_CR( void );
void wifi_uart_send_code( char * name, uint8_t code );
void wifi_uart_put_buf( const uint8_t * data, uint16_t len );

uint8_t get_wifi_buffer( char ** buf );
WiFi_config_t * wifi_get_config( void );

void wifi_connect( void );

void wifi_init( UART_HandleTypeDef * uart );

void server_init( void );

#endif /* APPLICATION_USER_WIFI_WIFI_H_ */
