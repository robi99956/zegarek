/*
* scheduler.h
*
*  Created on: 22 wrz 2018
*      Author: Robert Krauze
*/

#ifndef APPLICATION_USER_SCHEDULER_SCHEDULER_H_
#define APPLICATION_USER_SCHEDULER_SCHEDULER_H_

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

#include "system.h"

#include <stdint.h>

typedef void(*task_callback)(void);
typedef uint8_t scheduler_flags_t;

typedef enum _delay_units { DELAY_MILLISECONDS = 1, DELAY_SECONDS = 1000, DELAY_MINUTES = 60 * 1000, DELAY_HOURS = 60 * 60 * 1000 } delay_units_t;

#define REQUIRES_UART_ANSWER 0x01
#define REPEATABLE 0x80

typedef struct _task
{
	uint32_t start_tick;
	uint32_t delay;
	task_callback callback;

	uint8_t flags;

	struct _task * next;
} task;

typedef task* task_handle_t;

task_handle_t scheduler_add_task(task_callback callback, uint32_t delay, delay_units_t delay_unit, scheduler_flags_t flags);
void scheduler_remove_task(task_handle_t __task);
void scheduler_pool(void);
void scheduler_unlock(scheduler_flags_t flags_to_remove);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* APPLICATION_USER_SCHEDULER_SCHEDULER_H_ */
