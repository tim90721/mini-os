#include <errno.h>
#include <stdint.h>
#include <stdlib.h>

#include <interrupt.h>

int trap_init(void)
{
	/* unmask CPU debug, exceptions, irq, fiq */
	__asm__ __volatile__(
		"msr DAIFClr, #0xF"
	);

	return 0;
}

void el1h_64_sync_handler(void)
{
	/* TODO */
}

void el1h_64_irq_handler(void)
{
	if (!arch_irq_handler)
		exit(-ENODEV);

	arch_irq_handler();
}

void el1h_64_fiq_handler(void)
{
	/* TODO */
}

void el1h_64_serror_handler(void)
{
	/* TODO */
}
