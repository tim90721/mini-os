#include <compiler.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include <mm/mm.h>
#include <sched.h>
#include <time.h>

#include <platform/platform.h>

static void task1(void *param)
{
	while (1) {
		printf("task1 running, tick: %u\n", tick);

		msleep(1000);
	}
}

static void task2(void *param)
{
	while (1) {
		printf("task2 running, tick: %u\n", tick);

		msleep(5000);
	}
}

int start_kernel(void)
{
	int ret;

	ret = memory_init();
	if (unlikely(ret))
		exit(ret);

	ret = platform_init();
	if (unlikely(ret))
		exit(ret);

	ret = time_init();
	if (unlikely(ret))
		exit(ret);

	ret = sched_init();
	if (unlikely(ret))
		exit(ret);

	ret = task_create(task1, NULL, PAGE_SIZE);
	if (ret) {
		printf("create init task failed: %d\n", ret);
		return ret;
	}

	ret = task_create(task2, NULL, PAGE_SIZE);
	if (ret) {
		printf("create task2 failed: %d\n", ret);
		return ret;
	}

	schedule();

	while (1) {
		if (sched_has_task_woken())
			schedule();
	}

	return 0;
}
