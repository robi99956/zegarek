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
#include "../RTC/rtc.h"

void MX_USB_DEVICE_Init(void);
static void send_file( char * filename );
char * prepare_filename( char * filename );
void send_file_task( task_handle_t task );
void server_post_task( task_handle_t task );

task_handle_t post_task_handle;

DIR dir;

static char * new_time;

uint8_t send_file_callback( char * message )
{
	if( strcmp(message, "FILE READY") == 0 )
	{
		send_file( prepare_filename(NULL) );
	}
	else
	if( (strcmp(message, "FILE OK") == 0) || (strcmp(message, "FILE ERROR") == 0) )
	{
		scheduler_add_task(send_file_task, 0, 0, REQUIRES_UART_ANSWER, NULL);
		scheduler_unlock(REQUIRES_UART_ANSWER);
	}

	return 1;
}

void send_file_task( task_handle_t task )
{
	UNUSED(task);

	FILINFO info;
	FRESULT res;

	res = f_readdir(&dir, &info);

	if( info.fname[0] == 0 || res != FR_OK )
	{
		scheduler_unlock(REQUIRES_UART_ANSWER);
		f_closedir(&dir);
		f_unmount();
		MX_USB_DEVICE_Init();
		return;
	}

	if( info.fattrib & AM_DIR )
	{
		scheduler_add_task(send_file_task, 0, 0, REQUIRES_UART_ANSWER, NULL);
		scheduler_unlock(REQUIRES_UART_ANSWER);
		return;
	}

	wifi_uart_puts("FILE ");
	wifi_uart_puts( prepare_filename(info.fname) );
	wifi_uart_send_space();
	wifi_uart_putint( info.fsize, 10 );
	wifi_uart_send_CR();

	wifi_uart_callback_register( send_file_callback );
}

void server_init( void )
{
	FRESULT res;

	res = f_opendir(&dir, "/strona");
	f_chdir("/strona");
	if( res != FR_OK ) return;

	scheduler_add_task(send_file_task, 0, 0, REQUIRES_UART_ANSWER, NULL);
	scheduler_add_task(server_post_task, 10, DELAY_SECONDS, REPEATABLE | REQUIRES_UART_ANSWER, NULL);
}

void change_config( char * message )
{
	char * name = strtok(message, "=");
	char * value = strtok(NULL, "\r");

	WiFi_config_t * config = wifi_get_config();

	if( strcmp(name, "msc_zap") == 0 ) 			strcpy(config->loc_api_info.url, value);
	else if( strcmp(name, "czas_zap") == 0 )	strcpy(config->time_api_info.url, value);
	else if( strcmp(name, "lat") == 0 )			strcpy(config->loc_api_info.marker_lat, value);
	else if( strcmp(name, "lon") == 0 )			strcpy(config->loc_api_info.marker_lon, value);
	else if( strcmp(name, "czas_mark") == 0 )	strcpy(config->time_api_info.marker, value);
	else if( strcmp(name, "kraj") == 0 )		strcpy(config->country_code, value);
	else if( strcmp(name, "haslo") == 0 )		strcpy(config->connect_info.passwd, value);
	else if( strcmp(name, "ntp_adres") == 0 )	strcpy(config->ntp_info.ip, value);
	else if( strcmp(name, "gmtoffset") == 0 )	config->gmt_offset = atoi(value);
	else if( strcmp(name, "dataczas") == 0 )
	{
		new_time = (char*)malloc( strlen(value)+1 );
		if( new_time == NULL ) return;
		strcpy(new_time, value);
	}
	else if( strcmp(name, "_ssid") == 0 )
	{
		if( value[0] != 0 ) strcpy(config->connect_info.ssid, value);
	}
	else if( strcmp(name, "ssid") == 0 )
	{
		if( value[0] != 0 ) strcpy(config->connect_info.ssid, value);
	}
	else if( strcmp(name, "type") == 0 )
	{
		if( strcmp(value, "LOCTIME") == 0 ) config->mode = API_LOCTIME;
		else if( strcmp(value, "TIME") == 0 ) config->mode = API_TIME;
		else if( strcmp(value, "NTP") == 0 ) config->mode = NTP;
		else if( strcmp(value, "MANUAL") == 0 ) config->mode = MANUAL;
	}
	else if( strcmp(name, "lato_zima") == 0 )
	{
		if( strcmp(value, "on") == 0 )
		{
			config->use_summerwinter_time = 1;
			return;
		}
	}

	config->use_summerwinter_time = 0;
}

uint8_t server_post_callback( char * message )
{
	uint8_t retval=0;

	if( strcmp(message, "POST NONE") == 0 )
	{
		retval = 1;
	}
	else
	if( strcmp(message, "POST END") == 0 )
	{
		WiFi_config_t * config = wifi_get_config();
		wifi_save_config(config);

		f_unmount();

		if( new_time != NULL )
		{
			rtc_set_time_manual(new_time);
			free(new_time);
			new_time = NULL;
		}

		retval = 1;
	}
	else
	if( strcmp(message, "POST START") == 0 )
	{
		usb_disconnect();
	}
	else
	if( strncmp(message, "POST ", 5) == 0 )
	{
		change_config(message+5);
		retval = 1;
	}

	if(retval) scheduler_unlock(REQUIRES_UART_ANSWER);

	return retval;
}

void server_post_task( task_handle_t task )
{
	UNUSED(task);

	static const char cmd[] = "POST\r";
	wifi_uart_puts(cmd);

	wifi_uart_callback_register(server_post_callback);
}

char * prepare_filename( char * filename )
{
	static char name[15];
	static const char glowny[] = "INDEX.HTM";

	if( filename == NULL )
	{
		if( name[0] == '/' && name[1] == 0 )  return (char*)glowny;

		return name+1;
	}

	name[0] = '/'; name[1] = 0;

	if( strcmp(filename, glowny) == 0 ) return name;

	strcpy(name+1, filename);

	return name;
}

static void send_file( char * filename )
{
	FRESULT res;
	char * buf;
	uint8_t buf_size = get_wifi_buffer(&buf)-1;
	UINT br=buf_size;

	res = f_open(&USERFile, filename, FA_READ);

	if( res != FR_OK ) return;

	do
	{
		memset(buf, 0, buf_size+1);
		res = f_read(&USERFile, buf, buf_size, &br);

		wifi_uart_put_buf((uint8_t*)buf, br);

	}while( br == buf_size );

	f_close(&USERFile);
}

