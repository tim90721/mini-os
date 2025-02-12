#include <compiler.h>

#include <drivers/irqchip/irqchip-gic-v2.h>
#include <drivers/uart/uart_pl011.h>

#include <platform/platform.h>

int platform_init(void)
{
	int ret;

	ret = gic_init();
	if (unlikely(ret))
		return ret;

	ret = uart_pl011_init();
	if (unlikely(ret))
		return ret;

	return 0;
}
