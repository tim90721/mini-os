#include <stdio.h>

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <align.h>
#include <compiler.h>
#include <list.h>
#include <mm/mm.h>
#include <sched.h>
#include <task.h>

struct task_struct *current;
LIST_NODE(task_list);

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
	list_add_tail(&task->node, &task_list);

	return 0;
}

void schedule(void)
{
	struct task_struct *next;

	if (unlikely(list_empty(&task_list)))
		exit(0);

	next = list_first_entry(&task_list, struct task_struct, node);
	if (next == current)
		return;

	list_del(&next->node);
	if (current)
		list_add_tail(&current->node, &task_list);

	current = next;
	switch_to(&current->ctx);
}
