/*
* scheduler.c
*
*  Created on: 22 wrz 2018
*      Author: Robert Krauze
*/
#include "system.h"
#include <stdlib.h>

#include "scheduler.h"

static task_handle_t list;
static scheduler_flags_t flags;

task_handle_t scheduler_add_task(task_callback callback, uint32_t delay, delay_units_t delay_unit, scheduler_flags_t flags, void * arg)
{
	task_handle_t ptr = list;

	if (ptr != NULL)
	{
		while (ptr->next != NULL)
		{
			ptr = (task_handle_t)ptr->next;
		}

		ptr->next = (task_handle_t)malloc(sizeof(task));
		if (ptr->next == NULL) return NULL;

		ptr = (task_handle_t)ptr->next;
	}
	else
	{
		ptr = (task_handle_t)malloc(sizeof(task));
		if (ptr == NULL) return NULL;
		list = ptr;
	}

	ptr->callback = callback;
	ptr->start_tick = get_tick();
	ptr->delay = delay*delay_unit;
	ptr->flags = flags;
	ptr->arg = arg;
	ptr->next = NULL;

	return ptr;
}

void scheduler_remove_task(task_handle_t __task)
{
	if( __task == NULL ) return;

	task_handle_t ptr = list;
	task_handle_t prev = NULL;

	while (ptr)
	{
		if ( ptr == __task )
		{
			if (prev) prev->next = ptr->next;

			if (ptr == list) list = (task_handle_t)ptr->next;

			free(ptr);
			__task = NULL;

			return;
		}

		prev = ptr;
		ptr = (task_handle_t)ptr->next;
	}
}

void scheduler_unlock(scheduler_flags_t flags_to_remove)
{
	flags &= ~flags_to_remove;
}

void scheduler_pool(void)
{
	static uint32_t last_tick;
	uint32_t tick = get_tick();

	if( tick == last_tick ) return;

	last_tick = tick;

	task_handle_t ptr = list;
	task_handle_t prev = NULL;

	task_callback callback;

	while (ptr)
	{
		if ( tick - ptr->start_tick >= ptr->delay )
		{
			scheduler_flags_t ptr_flags = ptr->flags & BLOCKING_FLAGS_MASK;

			if (flags & ptr_flags) goto NEXT_TASK;

			callback = ptr->callback;

			flags |= ptr_flags;

			if (callback) callback(ptr);

			if ( (ptr->flags & REPEATABLE) == 0 || (ptr->flags & DELETE_ASAP) )
			{
				if (prev) prev->next = ptr->next;

				if (ptr == list) list = (task_handle_t)ptr->next;

				free(ptr);
			}
			else
			{
				ptr->start_tick = tick;
			}
			return;
		}

	NEXT_TASK:
		prev = ptr;
		ptr = (task_handle_t)ptr->next;
	}
}
