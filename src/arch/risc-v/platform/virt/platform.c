#include <platform/platform.h>

#include <drivers/uart/uart_16550A.h>

int platform_init(void)
{
	return uart_init();
}
