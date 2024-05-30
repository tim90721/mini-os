#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include <mm/mm.h>
#include <sched.h>

#include <platform/platform.h>

void task_a(void *param)
{
	int i = 0;

	while (1) {
		printf("a start\n");

		while (i < 10000000)
			i++;

		i = 0;
	}
}

int start_kernel(void)
{
	int ret;

	ret = platform_init();
	if (ret)
		exit(ret);

	memory_init();

	printf("hello kernel\n");

	ret = task_create(task_a, NULL, PAGE_SIZE);
	if (ret) {
		printf("create task failed: %d\n", ret);
		return 0;
	}

	schedule();

	return 0;
}
