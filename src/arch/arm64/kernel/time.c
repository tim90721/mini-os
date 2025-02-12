#include <compiler.h>
#include <errno.h>
#include <interrupt.h>
#include <stddef.h>
#include <stdint.h>
#include <time.h>

static u32 HZ = CONFIG_TIMER_INTERVAL;

static void arm_timer_enable(bool en)
{
	__asm__ __volatile__(
		"mov x0, #1\n"
		"msr cntp_ctl_el0, x0"
		:
		:
		: "memory");
}

static void arm_timer_reconfig(u32 val)
{
	__asm__ __volatile__(
		"msr cntp_tval_el0, %[timer_val]"
		:
		: [timer_val] "r" (val)
		: "memory");
}

static int arm_timer_irq_handler(void *param)
{
	tick++;
	arm_timer_reconfig(HZ);

	return 0;
}

static int arm_timer_irq_setup(void)
{
	struct irq_desc *desc = irq_desc_get(IRQCHIP_GIC, IRQ_PPI_NON_SECURE_TIMER);

	if (unlikely(!desc))
		return -ENODEV;

	request_irq(desc, arm_timer_irq_handler, NULL);
	irq_set_priority(desc, 0);
	irq_enable(desc);

	return 0;
}

int arch_time_init(void)
{
	int ret;

	/* request timer irq */
	ret = arm_timer_irq_setup();
	if (unlikely(ret))
		return ret;

	/* add time to tval */
	arm_timer_reconfig(HZ);

	/* enable interrupt */
	arm_timer_enable(1);

	return 0;
}
