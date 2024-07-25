#include <time.h>

u32 tick = 0;

int time_init(void)
{
	return arch_time_init();
}
