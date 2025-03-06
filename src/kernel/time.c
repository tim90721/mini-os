#include <sched.h>
#include <time.h>

size_t tick = 0;

void time_tick(void)
{
	tick++;
	sched_check_tick();
}

int time_init(void)
{
	return arch_time_init();
}
