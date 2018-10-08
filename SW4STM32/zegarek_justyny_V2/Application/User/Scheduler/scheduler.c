/*
* scheduler.c
*
*  Created on: 22 wrz 2018
*      Author: Robert
*/
#include <stdlib.h>
#include "stm32f0xx_hal.h"

#include "scheduler.h"

task * list;

void scheduler_add_task(task_callback callback, uint32_t delay, delay_units_t delay_unit, uint8_t flags)
{
	task * ptr = list;

	if (ptr != NULL)
	{
		while (ptr->next != NULL)
		{
			ptr = (task*)ptr->next;
		}

		ptr->next = (task*)malloc(sizeof(task));
		if (ptr->next == NULL) return;

		ptr = (task*)ptr->next;
	}
	else
	{
		ptr = (task*)malloc(sizeof(task));
		if (ptr == NULL) return;
		list = ptr;
	}

	ptr->callback = callback;
	ptr->start_tick = HAL_GetTick();
	ptr->execute_tick = delay*delay_unit + ptr->start_tick;
	ptr->flags = flags;
	ptr->next = NULL;
}

static uint8_t flags;

void scheduler_unlock(uint8_t flags_to_remove)
{
	flags &= ~flags_to_remove;
}

void scheduler_pool(void)
{
	uint32_t tick = HAL_GetTick();

	task * ptr = list;
	task * prev = NULL;

	task_callback callback;

	while (ptr)
	{
		if (ptr->execute_tick <= tick || ptr->start_tick > tick)
		{
			if (flags & ptr->flags) goto NEXT_TASK;

			callback = ptr->callback;

			flags |= ptr->flags;

			if (prev) prev->next = ptr->next;

			if (ptr == list) list = (task*)ptr->next;

			free(ptr);

			if( callback ) callback();

			return;
		}

	NEXT_TASK:
		prev = ptr;
		ptr = (task*)ptr->next;
	}
}
