#include <time.h>

size_t tick = 0;

int time_init(void)
{
	return arch_time_init();
}
