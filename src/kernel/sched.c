#include <stdio.h>

#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <align.h>
#include <compiler.h>
#include <irq.h>
#include <list.h>
#include <mm/mm.h>
#include <sched.h>
#include <task.h>
#include <time.h>

struct task_struct *current;
static struct task_struct idle_task;

static LIST_NODE(task_list);
static LIST_NODE(idle_list);
static bool task_has_woken;

int task_create(void (*task_func)(void *param), void *param, u32 stack_size)
{
	struct task_struct *task;

	if (unlikely(!task_func))
		return -EINVAL;

	/* align stack size to PAGE_SIZE */
	stack_size = ALIGN(stack_size + sizeof(struct task_struct), PAGE_SIZE);

	/* task struct occupies the start of page */
	task = alloc_page(stack_size / PAGE_SIZE);
	if (unlikely(!task))
		return -ENOMEM;

	/* initialize task struct */
	list_node_init(&task->node);
	memset(task, 0, stack_size);

	/* architechure dependent initialization */
	__task_create(task, task_func, param, stack_size);

	/* append new task to task list */
	/* TODO: should upgrade to spinlock */
	disable_irq();
	list_add_tail(&task->node, &task_list);
	enable_irq();

	return 0;
}

bool sched_has_task_woken(void)
{
	bool ret;

	/* TODO: should upgrade to spinlock */
	disable_irq();

	ret = task_has_woken;

	enable_irq();

	return ret;
}

void sched_check_tick(void)
{
	struct task_struct *task;
	struct task_struct *tmp;

	list_for_each_entry_safe(task, tmp, &idle_list, node) {
		if (tick >= task->wakeup_tick) {
			task_has_woken = true;
			task->flag &= ~TASK_FLAG_SLEEP;
			list_del(&task->node);
			list_add_tail(&task->node, &task_list);
		}
	}
}

void schedule(void)
{
	struct task_struct *prev = NULL;
	struct task_struct *next;

	/* TODO: should upgrade to spinlock */
	disable_irq();

	if (current->flag & TASK_FLAG_SLEEP)
		list_add_tail(&current->node, &idle_list);
	else if (current != &idle_task)
		list_add_tail(&current->node, &task_list);

	if (!list_empty(&task_list)) {
		next = list_first_entry(&task_list, struct task_struct, node);
		list_del(&next->node);
		task_has_woken = false;
	} else {
		next = &idle_task;
	}

	enable_irq();

	if (next == current)
		return;

	prev = current;
	current = next;
	switch_to(prev, next);
}

int sched_init(void)
{
	current = &idle_task;
	task_has_woken = false;

	return 0;
}
