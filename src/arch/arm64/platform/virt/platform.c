#include <platform/platform.h>

#include <drivers/uart/uart_pl011.h>

int platform_init(void)
{
	int ret;

	ret = uart_pl011_init();
	if (ret)
		return ret;

	return 0;
}

