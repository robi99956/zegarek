/*
 * config.c
 *
 *  Created on: 23 paü 2018
 *      Author: Robert
 */

#include <string.h>
#include <stdlib.h>

#include "wifi.h"
#include "fatfs.h"
#include "../Scheduler/scheduler.h"

#define CHECK_RES(res) if(res!=FR_OK)return

static const char config_file_begin[] = "<config>\n";
static const char config_file_end[] = "</config>";

static const char mode_name[] = "MODE";
static const char ssid_name[] = "SSID";
static const char passwd_name[] = "PASSWD";
static const char time_mark_name[] = "TIME_MARK";
static const char time_url_name[] = "TIME_URL";
static const char loc_url_name[] = "LOC_URL";
static const char lat_mark_name[] = "LAT_MARK";
static const char lon_mark_name[] = "LON_MARK";
static const char ntp_ip_name[] = "NTP_IP";
static const char time_format_name[] = "TIME_FORMAT";
static const char country_code_name[] = "C_CODE";
static const char gmt_offset_name[] = "GMT_OFFSET";
static const char summer_winter_time_name[] = "SUM_WIN";

void wifi_save_parameter( const char * name, char * value )
{
	f_putc('<', &USERFile);
	f_puts(name, &USERFile);
	f_putc('>', &USERFile);

	f_puts(value, &USERFile);

	f_puts("</", &USERFile);
	f_puts(name, &USERFile);
	f_puts(">\n", &USERFile);
}

void wifi_save_config( WiFi_config_t * config )
{
	FRESULT res;

	res = f_forcemount(0);
	CHECK_RES(res);

	res = f_open(&USERFile, "/config.xml", FA_CREATE_ALWAYS | FA_WRITE);
	CHECK_RES(res);

	char int_buf[10];

	f_puts(config_file_begin, &USERFile);

	itoa(config->mode, int_buf, 10);
	wifi_save_parameter(mode_name, int_buf);

	wifi_save_parameter(ssid_name, config->connect_info.ssid);
	wifi_save_parameter(passwd_name, config->connect_info.passwd);

	wifi_save_parameter(time_mark_name, config->time_api_info.marker);
	wifi_save_parameter(time_url_name, config->time_api_info.url);

	wifi_save_parameter(loc_url_name, config->loc_api_info.url);
	wifi_save_parameter(lon_mark_name, config->loc_api_info.marker_lon);
	wifi_save_parameter(lat_mark_name, config->loc_api_info.marker_lat);

	wifi_save_parameter(ntp_ip_name, config->ntp_info.ip);

	wifi_save_parameter(time_format_name, config->time_format);

	wifi_save_parameter(country_code_name, config->country_code);

	itoa(config->gmt_offset, int_buf, 10);
	wifi_save_parameter(gmt_offset_name, int_buf);

	itoa(config->use_summerwinter_time, int_buf, 10);
	wifi_save_parameter(summer_winter_time_name, int_buf);

	f_puts(config_file_end, &USERFile);

	f_close(&USERFile);

	f_unmount();
}

void wifi_read_parameter( char * name, char * value, WiFi_config_t * config )
{
	if( strcmp(name, mode_name) == 0 ) config->mode = *value-'0';
	else if( strcmp(name, ssid_name) == 0 ) strcpy(config->connect_info.ssid, value);
	else if( strcmp(name, passwd_name) == 0 ) strcpy(config->connect_info.passwd, value);
	else if( strcmp(name, time_mark_name) == 0 ) strcpy(config->time_api_info.marker, value);
	else if( strcmp(name, time_url_name) == 0 ) strcpy(config->time_api_info.url, value);
	else if( strcmp(name, loc_url_name) == 0 ) strcpy(config->loc_api_info.url, value);
	else if( strcmp(name, lat_mark_name) == 0 ) strcpy(config->loc_api_info.marker_lat, value);
	else if( strcmp(name, lon_mark_name) == 0 ) strcpy(config->loc_api_info.marker_lon, value);
	else if( strcmp(name, ntp_ip_name) == 0 ) strcpy(config->ntp_info.ip, value);
	else if( strcmp(name, time_format_name) == 0 ) strcpy(config->time_format, value);
	else if( strcmp(name, country_code_name) == 0 ) strcpy(config->country_code, value);
	else if( strcmp(name, gmt_offset_name) == 0 ) config->gmt_offset = atoi(value);
	else if( strcmp(name, summer_winter_time_name) == 0 ) config->use_summerwinter_time = *value-'0';
}

void wifi_read_config( WiFi_config_t * config )
{
	FRESULT res;

	res = f_forcemount(0);
	CHECK_RES(res);

	res = f_open(&USERFile, "/config.xml", FA_OPEN_EXISTING | FA_READ);
	CHECK_RES(res);

	char line_buf[240];
	char * name, * value, * tmp;

	while( f_eof(&USERFile) == 0 )
	{
		if( f_gets(line_buf, sizeof(line_buf)-1, &USERFile) == NULL ) break;

		if( strncmp(line_buf, config_file_begin, sizeof(config_file_begin)-2) == 0 ||
			strncmp(line_buf, config_file_end, sizeof(config_file_end)-1) == 0 ) continue;

		name = line_buf+1;
		tmp = strchr(name, '>');

		*tmp = 0;

		value = tmp+1;
		*strstr(value, "</") = 0;

		wifi_read_parameter(name, value, config);
	}

	f_close(&USERFile);
}
