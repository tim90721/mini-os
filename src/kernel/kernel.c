#include <stdio.h>
#include <stdlib.h>

#include <drivers/test_driver.h>

int start_kernel(void)
{
	//printf("%s hello\n", __func__);

	test_driver_hello();

	return 0;
}
