#include <compiler.h>
#include <task.h>
#include <types.h>

void __task_create(struct task_struct *task,
		   void (*task_func)(void *param), void *param, u32 stack_size)
{
	if (!task || !task_func)
		return;

	task->ctx.ra = (reg_t)task_func;
	task->ctx.sp = (reg_t)((addr_t)task + stack_size);

	if (param)
		task->ctx.a0 = (reg_t)param;
	else
		task->ctx.a0 = 0;
}
