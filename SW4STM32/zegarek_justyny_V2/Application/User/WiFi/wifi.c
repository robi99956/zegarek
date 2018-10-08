/*
 * wifi.c
 *
 *  Created on: 21 wrz 2018
 *      Author: Robert
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "wifi.h"
#include "../Scheduler/scheduler.h"

static WiFi_config_t wifi_config;
static wifi_string wifi_list[20];

void wifi_connect( void );
void wifi_keep_connected_task( void );
void wifi_reset( void );
void wifi_make_wifi_list_task( void );
void wifi_getip_task( void );

void wifi_set_config( WiFi_config_t * config )
{
	memcpy(&wifi_config, config, sizeof(WiFi_config_t) );
}

WiFi_config_t * wifi_get_config( void )
{
	return &wifi_config;
}

uint8_t IP_to_str( IP_t ip, char * dst )
{
	return sprintf(dst, "%d.%d.%d.%d", ip.bytes[0], ip.bytes[1], ip.bytes[2], ip.bytes[3]);
}

void wifi_write_config_manual( WiFi_config_t * config )
{
	(void)config;

	static const char cmd[] = "CONFIG MANUAL\r";
	wifi_uart_puts(cmd);
}

void wifi_write_config_ntp( WiFi_config_t * config )
{
	static const char cmd[] = "CONFIG NTP ";
	char ip_buf[20];

	wifi_uart_puts(cmd);

	wifi_uart_puts(config->ntp_info.ip);
	wifi_uart_send_space();

	wifi_uart_puts(config->time_format);
	wifi_uart_send_space();

	wifi_uart_putint(config->gmt_offset, 10);
	wifi_uart_send_space();

	wifi_uart_putint(config->use_summerwinter_time, 10);
	wifi_uart_send_CR();
}

void wifi_write_config_time_api( WiFi_config_t * config )
{
	static const char cmd[] = "CONFIG TIME ";

	wifi_uart_puts(cmd);

	wifi_uart_puts(config->time_api_info.url);
	wifi_uart_send_space();

	wifi_uart_puts(config->time_api_info.marker);
	wifi_uart_send_space();

	wifi_uart_puts(config->time_format);
	wifi_uart_send_space();

	wifi_uart_putint(config->gmt_offset, 10);
	wifi_uart_send_space();

	wifi_uart_putint(config->use_summerwinter_time, 10);

	wifi_uart_send_CR();
}

void wifi_write_config_loctime_api( WiFi_config_t * config )
{
	static const char cmd[] = "CONFIG LOCTIME ";

	wifi_uart_puts(cmd);

	wifi_uart_puts(config->loc_api_info.url);
	wifi_uart_send_space();

	wifi_uart_puts(config->time_api_info.url);
	wifi_uart_send_space();

	wifi_uart_puts(config->loc_api_info.marker_lon);
	wifi_uart_send_space();

	wifi_uart_puts(config->loc_api_info.marker_lat);
	wifi_uart_send_space();

	wifi_uart_puts(config->time_api_info.marker);
	wifi_uart_send_space();

	wifi_uart_puts(config->time_format);
	wifi_uart_send_CR();
}

uint8_t wifi_write_config_callback( char * answer )
{
	uint8_t retval=0;

	if( strcmp(answer, "ERROR") == 0 )
	{
		retval = 1;
	}
	else
		if( strcmp(answer, "OK") == 0 )
		{
			retval = 1;
		}

	if( retval ) scheduler_unlock(REQUIRES_UART_ANSWER);

	return retval;
}

void wifi_write_config( void )
{
	static const config_fun configs[4] = {
			wifi_write_config_manual, wifi_write_config_ntp,
			wifi_write_config_time_api, wifi_write_config_loctime_api
	};

	wifi_uart_callback_register(wifi_write_config_callback);

	configs[wifi_config.mode](&wifi_config);
}

uint8_t wifi_connect_callback( char * answer )
{
	static uint8_t fails;
	uint8_t retval=0;

	if( strcmp(answer, "CONNECT OK") == 0 )
	{
		scheduler_add_task(wifi_write_config, 0, 0, REQUIRES_UART_ANSWER);
		scheduler_add_task(wifi_keep_connected_task, 1, DELAY_MINUTES, REQUIRES_UART_ANSWER);
		scheduler_add_task(wifi_getip_task, 5, DELAY_SECONDS, REQUIRES_UART_ANSWER);

		fails = 0;

		retval = 1;
	}
	else
		if( strcmp( answer, "CONNECT ERROR") == 0 )
		{
			scheduler_add_task(wifi_connect, 30, DELAY_SECONDS, REQUIRES_UART_ANSWER);

			if( fails++ == 20 )
			{
				fails = 0;
				wifi_reset();
			}
			else
			{
				scheduler_add_task(wifi_connect, 30, DELAY_SECONDS, REQUIRES_UART_ANSWER);
			}

			retval = 1;
		}

	if( retval ) scheduler_unlock(REQUIRES_UART_ANSWER);

	return retval;
}

void wifi_connect( void )
{
	static const char cmd[] = "CONNECT ";

	strcpy(wifi_config.connect_info.ssid, "TP-LINK_E6001A");
	strcpy(wifi_config.connect_info.passwd, "995760ROBERT");
	wifi_config.mode = MANUAL;

	wifi_uart_puts( cmd );
	wifi_uart_puts( wifi_config.connect_info.ssid );
	wifi_uart_send_space();
	wifi_uart_puts( wifi_config.connect_info.passwd );
	wifi_uart_send_CR();

	wifi_uart_callback_register( wifi_connect_callback );
}

uint8_t wifi_keep_connected_callback( char * answer )
{
	uint8_t retval=0;
	if( strcmp(answer, "STATUS DISCONNECTED") == 0 )
	{
		scheduler_add_task(wifi_connect, 30, DELAY_SECONDS, REQUIRES_UART_ANSWER);
		retval = 1;
	}
	else
		if( strcmp(answer, "STATUS CONNECTED") == 0 )
		{
			scheduler_add_task(wifi_keep_connected_task, 1, DELAY_MINUTES, REQUIRES_UART_ANSWER);
			retval = 1;
		}

	if( retval ) scheduler_unlock(REQUIRES_UART_ANSWER);

	return retval;
}

void wifi_keep_connected_task( void )
{
	static const char cmd[] = "STATUS\r";
	wifi_uart_puts(cmd);

	wifi_uart_callback_register(wifi_keep_connected_callback);
}

void wifi_reset_task( void )
{
	wifi_uart_init();

	scheduler_add_task(wifi_connect, 0, 0, REQUIRES_UART_ANSWER);
}

void wifi_reset( void )
{
	static const char cmd[] = "RESET\r";
	wifi_uart_puts(cmd);

	wifi_uart_deinit();

	scheduler_add_task(wifi_reset_task, 3, DELAY_SECONDS, 0);
}

uint8_t wifi_make_wifi_list_callback( char * answer )
{
	uint8_t retval=0;
	static uint8_t ssid_idx;

	if( strcmp(answer, "WIFI LIST END") == 0 )
	{
		retval = 1;
		scheduler_unlock(REQUIRES_UART_ANSWER);

		scheduler_add_task(wifi_make_wifi_list_task, 1, DELAY_MINUTES, REQUIRES_UART_ANSWER);
	}
	else
		if( strcmp(answer, "WIFI LIST START") == 0 )
		{
			ssid_idx = 0;

			for( uint8_t i=0; wifi_list[i].len; i++ )
			{
				wifi_list[i].len = 0;
				free( wifi_list[i].s );
			}

			retval = 1;
		}
		else
			if( strncmp(answer, "WIFI ", 5) == 0 && ssid_idx < (sizeof(wifi_list)/sizeof(wifi_string)) )
			{
				answer += 5;
				uint8_t len = strlen(answer);

				wifi_list[ssid_idx].len = len;
				wifi_list[ssid_idx].s = (char*)malloc(len);

				memcpy(wifi_list[ssid_idx].s, answer, len);

				retval = 1;

				ssid_idx++;
			}

	return retval;
}

void wifi_make_wifi_list_task( void )
{
	static const char cmd[] = "SCAN\r";
	wifi_uart_puts(cmd);

	wifi_uart_callback_register(wifi_make_wifi_list_callback);
}

uint8_t wifi_getip_callback( char * answer )
{
	(void)answer;

	scheduler_unlock(REQUIRES_UART_ANSWER);

	return 1;
}

void wifi_getip_task( void )
{
	static const char cmd[] = "GETIP\r";
	wifi_uart_puts(cmd);

	wifi_uart_callback_register(wifi_getip_callback);
}

void wifi_init( UART_HandleTypeDef * uart )
{
	  wifi_uart_handle_register(uart);
	  wifi_uart_start_rec();

	  scheduler_add_task(wifi_connect, 0, 0, REQUIRES_UART_ANSWER);
	  scheduler_add_task(wifi_make_wifi_list_task, 300, DELAY_MILLISECONDS, REQUIRES_UART_ANSWER);

	  server_init();
}
