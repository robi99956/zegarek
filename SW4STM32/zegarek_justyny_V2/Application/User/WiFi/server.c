/*
 * server.c
 *
 *  Created on: 26 wrz 2018
 *      Author: Robert
 */

#include <string.h>
#include <stdlib.h>

#include "wifi.h"
#include "fatfs.h"
#include "../Scheduler/scheduler.h"

void server_get_task( void );

void server_init( void )
{
	scheduler_add_task(server_get_task, 1, DELAY_SECONDS, REQUIRES_UART_ANSWER | REPEATABLE);
}

static uint8_t str_beginswith( char * str, char * begin )
{
	uint16_t len = strlen(begin);

	return ( strncmp(str, begin, len) == 0 );
}

void change_config( char * message )
{
	char * name = strtok(message, "=");
	char * value = strtok(NULL, "\r");

	WiFi_config_t * config = wifi_get_config();

	if( strcmp(name, "msc_zap") ) 			strcpy(config->loc_api_info.url, value);
	else if( strcmp(name, "czas_zap") )		strcpy(config->time_api_info.url, value);
	else if( strcmp(name, "lat") )			strcpy(config->loc_api_info.marker_lat, value);
	else if( strcmp(name, "lon") )			strcpy(config->loc_api_info.marker_lon, value);
	else if( strcmp(name, "czas_mark") )	strcpy(config->time_api_info.marker, value);
	else if( strcmp(name, "kraj") )			strcpy(config->country_code, value);
	else if( strcmp(name, "_ssid") )		strcpy(config->connect_info.ssid, value);
	else if( strcmp(name, "haslo") )		strcpy(config->connect_info.passwd, value);
	else if( strcmp(name, "ntp_adres") )	strcpy(config->ntp_info.ip, value);

	else if( strcmp(name, "gmtoffset") )	config->gmt_offset = atoi(value);
	else if( strcmp(name, "dataczas") );
	else if( strcmp(name, "type") )
	{
		if( strcmp(value, "LOCTIME") ) config->mode = API_LOCTIME;
		else if( strcmp(value, "TIME") ) config->mode = API_TIME;
		else if( strcmp(value, "NTP") ) config->mode = NTP;
		else if( strcmp(value, "MANUAL") ) config->mode = MANUAL;
	}
}

uint8_t server_post_callback( char * message )
{

	return 0;
}

static char * get_filename( char * message )
{
	static const char index[] = "index.htm";
	char * ret = strchr(message, '/')+1;

	if( *ret == 0 ) return (char*)index;
	else return ret;
}

static void send_file( char * message )
{
	FRESULT res;
	char * buf;
	uint8_t buf_size = get_wifi_buffer(&buf)-1;
	UINT br=buf_size;

	char * filename = get_filename(message);

	res = f_open(&USERFile, filename, FA_READ);

	if( res != FR_OK )
	{
		wifi_uart_send_CR();
		return;
	}

	do
	{
		memset(buf, 0, buf_size+1);
		res = f_read(&USERFile, buf, buf_size, &br);

		wifi_uart_put_buf((uint8_t*)buf, br);

	}while( br == buf_size );

	wifi_uart_send_CR();

	f_close(&USERFile);
}

uint8_t server_get_callback( char * message )
{
	uint8_t retval=0;

	if( str_beginswith(message, "GET /") == 1 )
	{
		f_forcemount();
		f_chdir("/strona");

		send_file(message);

		retval = 1;
	}

	scheduler_unlock(REQUIRES_UART_ANSWER);
	return retval;
}

void server_get_task( void )
{
	static const char cmd[] = "GET\r";

	wifi_uart_callback_register(server_get_callback);
	wifi_uart_puts(cmd);
}
