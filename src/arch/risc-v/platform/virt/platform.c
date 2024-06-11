#include <arch/trap.h>
#include <platform/platform.h>

#include <drivers/irqchip/irqchip-plic.h>
#include <drivers/uart/uart_16550A.h>

int platform_init(void)
{
	int ret;

	ret = plic_init();
	if (ret)
		return ret;

	ret = trap_init();
	if (ret)
		return ret;

	ret = uart_init();
	if (ret)
		return ret;

	return 0;
}
