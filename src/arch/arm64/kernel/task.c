#include <stdint.h>
#include <task.h>

void __task_create(struct task_struct *task,
		   void (*task_func)(void *param), void *param, u32 stack_size)
{
	if (!task || !task_func)
		return;

	task->ctx.sp = (reg_t)((addr_t)task + stack_size);
	task->ctx.lr = (reg_t)task_func;

	if (param)
		task->ctx.x0 = (reg_t)param;
	else
		task->ctx.x0 = 0;
}
