#ifndef _TASK_H_
#define _TASK_H_

#include <stdint.h>

#include <bits.h>
#include <list.h>

#include <arch/context.h>

#define TASK_FLAG_SLEEP		BIT(TASK_FLAG_SLEEP_BIT)

enum task_flag_bit {
	TASK_FLAG_SLEEP_BIT,
};

struct task_struct {
	struct context ctx;
	struct list_node node;
	size_t wakeup_tick;
	u32 flag;
};

int task_create(void (*task_func)(void *param), void *param, u32 stack_size);
void __task_create(struct task_struct *task,
		   void (*task_func)(void *param), void *param, u32 stack_size);
#endif /* _TASK_H_ */
