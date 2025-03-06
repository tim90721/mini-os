#include <sched.h>
#include <time.h>

size_t tick = 0;

void msleep(u32 ms)
{
	current->wakeup_tick = tick + ms;
	current->flag |= TASK_FLAG_SLEEP;

	schedule();
}

void time_tick(void)
{
	tick++;
	sched_check_tick();
}

int time_init(void)
{
	return arch_time_init();
}
