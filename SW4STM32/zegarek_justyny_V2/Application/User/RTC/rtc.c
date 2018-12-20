/*
 * rtc.c
 *
 *  Created on: 28 wrz 2018
 *      Author: Robert
 */

#include "stm32f0xx_hal.h"

#include <string.h>

#include "rtc.h"
#include "../Scheduler/scheduler.h"
#include "../WiFi/wifi.h"
#include "../Led/led.h"

extern RTC_HandleTypeDef hrtc;

#define ERR_MAX 5

//2018-01-29 16:11
//rrrr-mm-dd gg-nn

void txt_to_czas( const char * buf, const char * pattern, RTC_TimeTypeDef * time, RTC_DateTypeDef * date )
{
  uint16_t wagi[6] = {1000, 10, 10, 10, 10, 10};
  memset(time, 0, sizeof(RTC_TimeTypeDef));
  memset(date, 0, sizeof(RTC_DateTypeDef));

  while( *pattern && *buf )
  {
    switch(*pattern)
    {
    case 'R': date->Year += wagi[0]*( *buf-'0' );
      wagi[0] /= 10;
      break;
    case 'M': date->Month += wagi[1]*( *buf-'0' );
      wagi[1] /= 10;
      break;
    case 'D': date->Date += wagi[2]*( *buf-'0' );
      wagi[2] /= 10;
      break;
    case 'g': time->Hours += wagi[3]*( *buf-'0' );
      wagi[3] /= 10;
      break;
    case 'm': time->Minutes += wagi[4]*( *buf-'0' );
      wagi[4] /= 10;
      break;
    case 's': time->Seconds += wagi[5]*( *buf-'0' );
      wagi[5] /= 10;
      break;
    }

    buf++;
    pattern++;
  }
}

uint8_t get_time_callback( char * answer )
{
	static uint8_t err_no;

	if( strncmp(answer, "TIME ", 5) == 0 )
	{
		if( answer[5] >= '0' && answer[5] <= '9')
		{
			RTC_TimeTypeDef time;
			RTC_DateTypeDef date;

			WiFi_config_t * config = wifi_get_config();

			txt_to_czas(answer+5, config->time_format, &time, &date);

			HAL_RTC_SetTime(&hrtc, &time, RTC_FORMAT_BIN);
			HAL_RTC_SetDate(&hrtc, &date, RTC_FORMAT_BIN);

			err_no = 0;
		}
		else
			if( strcmp(answer, "TIME ERROR") == 0 )
			{
				err_no++;

				if( err_no == ERR_MAX )
				{
					configure_try_connect();
				}
			}

		scheduler_unlock(REQUIRES_UART_ANSWER);
		return 1;
	}

	return 0;
}

void get_time_task( task_handle_t task )
{
	UNUSED(task);

	static const char cmd[] = "TIME\r";

	wifi_uart_callback_register(get_time_callback);
	wifi_uart_puts(cmd);
}

void show_time_task( task_handle_t task )
{
	UNUSED(task);

	RTC_TimeTypeDef time;
	RTC_DateTypeDef date;

	HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &date, RTC_FORMAT_BIN);

	led_show_time(&time);
}

void rtc_module_init( void )
{
	scheduler_add_task(get_time_task, 15, DELAY_SECONDS, REQUIRES_UART_ANSWER | REPEATABLE, NULL);
	scheduler_add_task(show_time_task, 500, DELAY_MILLISECONDS, REPEATABLE, NULL);
}


