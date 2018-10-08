/*
* scheduler.h
*
*  Created on: 22 wrz 2018
*      Author: Robert
*/

#ifndef APPLICATION_USER_SCHEDULER_SCHEDULER_H_
#define APPLICATION_USER_SCHEDULER_SCHEDULER_H_

typedef void(*task_callback)(void);

typedef enum _delay_units { DELAY_MILLISECONDS = 1, DELAY_SECONDS = 1000, DELAY_MINUTES = 60 * 1000, DELAY_HOURS = 60 * 60 * 1000 } delay_units_t;

#define REQUIRES_UART_ANSWER 1

typedef struct _task
{
	uint32_t start_tick;
	uint32_t execute_tick;
	task_callback callback;

	uint8_t flags;

	struct _task * next;
} task;

void scheduler_add_task(task_callback callback, uint32_t delay, delay_units_t delay_unit, uint8_t flags);
void scheduler_pool(void);
void scheduler_unlock(uint8_t flags_to_remove);

#endif /* APPLICATION_USER_SCHEDULER_SCHEDULER_H_ */
