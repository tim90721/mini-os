#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include <mm/mm.h>
#include <sched.h>
#include <time.h>

#include <platform/platform.h>

static void init_task(void *param)
{
	int i = 0;
	int ret;

	ret = platform_init();
	if (ret)
		exit(ret);

	while (1) {
		printf("task a running, tick: %u\n", tick);

		while (i < 100000000)
			i++;

		i = 0;
	}
}

int start_kernel(void)
{
	int ret;

	ret = memory_init();
	if (ret)
		exit(ret);

	ret = time_init();
	if (ret)
		exit(ret);

	printf("hello kernel\n");

	ret = task_create(init_task, NULL, PAGE_SIZE);
	if (ret) {
		printf("create init task failed: %d\n", ret);
		return ret;
	}

	schedule();

	return 0;
}
