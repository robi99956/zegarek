/*
 * rtc.h
 *
 *  Created on: 28 wrz 2018
 *      Author: Robert
 */

#ifndef APPLICATION_USER_RTC_RTC_H_
#define APPLICATION_USER_RTC_RTC_H_

#include <stdint.h>
#include "../Scheduler/scheduler.h"

void rtc_module_init( void );
void show_time_task( task_handle_t task );

#endif /* APPLICATION_USER_RTC_RTC_H_ */
