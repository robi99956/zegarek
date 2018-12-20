/*
* scheduler.h
*
*  Created on: 22 wrz 2018
*      Author: Robert Krauze
*/

#ifndef SCHEDULER_SCHEDULER_H_
#define SCHEDULER_SCHEDULER_H_

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

#include "system.h"

#include <stdint.h>

#define REQUIRES_UART_ANSWER 0x0001

#define DELETE_ASAP 0x4000
#define REPEATABLE 0x8000

#define BLOCKING_FLAGS_MASK (~(DELETE_ASAP | REPEATABLE))

typedef uint16_t scheduler_flags_t;

typedef enum _delay_units { DELAY_MILLISECONDS = 1, DELAY_SECONDS = 1000, DELAY_MINUTES = 60 * 1000, DELAY_HOURS = 60 * 60 * 1000 } delay_units_t;

typedef struct _task
{
	uint32_t start_tick;
	uint32_t delay;
	void(*callback)(struct _task*);

	scheduler_flags_t flags;

	void * arg;

	struct _task * next;
} task;

typedef task* task_handle_t;
typedef void(*task_callback)(task_handle_t);

task_handle_t scheduler_add_task(task_callback callback, uint32_t delay, delay_units_t delay_unit, scheduler_flags_t flags, void * arg);
void scheduler_remove_task(task_handle_t __task);
void scheduler_pool(void);
void scheduler_unlock(scheduler_flags_t flags_to_remove);

// funkcja do usuwania procesu z wnêtrza jego callbacka(usuwania samego siebie)
// ustawia flagê obs³ugiwan¹ dalej w scheduler_pool()
inline void scheduler_delayed_remove_task(task_handle_t __task)
{
	__task->flags |= DELETE_ASAP;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* APPLICATION_USER_SCHEDULER_SCHEDULER_H_ */
