#include <stdio.h>
#include <stdlib.h>

#include <platform/platform.h>

int start_kernel(void)
{
	int ret;

	ret = platform_init();
	if (ret)
		exit(ret);

	printf("hello kernel\n");

	return 0;
}
