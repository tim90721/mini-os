#include <stdio.h>

#include <errno.h>
#include <stddef.h>
#include <stdlib.h>

#include <bits.h>
#include <compiler.h>
#include <interrupt.h>
#include <mmio.h>

#include <drivers/irqchip/irqchip-plic.h>

static int plic_irq_enable(struct irq_desc *desc, bool en);
static int plic_irq_set_priority(struct irq_desc *desc, u32 priority);
static struct irq_desc *plic_irq_desc_get(enum irq_id id);

static struct irq_chip plic = {
	.irq_enable = plic_irq_enable,
	.irq_set_priority = plic_irq_set_priority,
	.irq_desc_get = plic_irq_desc_get,
};

static struct irq_desc plic_irqdescs[__NR_PLIC_IRQ] = {
	[0 ... __NR_PLIC_IRQ - 1] = {
		.action.irq_handler = unused_irq_handler,
		.chip = &plic,
	}
};

static inline u32 plic_read(u32 reg)
{
	return mmio_read_32(PLIC_BASE + reg);
}

static inline void plic_write(u32 reg, u32 val)
{
	mmio_write_32(PLIC_BASE + reg, val);
}

static inline void plic_set(u32 reg, u32 set)
{
	mmio_setbits_32(PLIC_BASE + reg, set);
}

static inline void plic_clr(u32 reg, u32 clr)
{
	mmio_clrbits_32(PLIC_BASE + reg, clr);
}

static inline enum plic_irq_id irq_desc_to_plic_irq_id(struct irq_desc *desc)
{
	if (unlikely(!desc || (desc->id - __PLIC_IRQ_ID_OFS >= __NR_PLIC_IRQ)))
		return __NR_PLIC_IRQ;

	return desc->id - __PLIC_IRQ_ID_OFS;
}

static int plic_irq_enable(struct irq_desc *desc, bool en)
{
	enum plic_irq_id pid = irq_desc_to_plic_irq_id(desc);

	if (unlikely(pid == __NR_PLIC_IRQ))
		return -EINVAL;

	/* TODO: need to consider multiple harts */
	if (en)
		plic_set(PLIC_IRQ_ENABLE(0, pid), BIT(pid % 32));
	else
		plic_clr(PLIC_IRQ_ENABLE(0, pid), BIT(pid % 32));

	return 0;
}

static int plic_irq_set_priority(struct irq_desc *desc, u32 priority)
{
	enum plic_irq_id pid = irq_desc_to_plic_irq_id(desc);

	if (unlikely(priority >= __PLIC_IRQ_PRIORITY_MAX
	    || pid == __NR_PLIC_IRQ))
		return -EINVAL;

	plic_write(PLIC_IRQ_PRIORITY(pid), priority);

	return 0;
}

static struct irq_desc *plic_irq_desc_get(enum irq_id id)
{
	enum plic_irq_id pid = id - __PLIC_IRQ_ID_OFS;

	if (pid >= __NR_PLIC_IRQ)
		return NULL;

	return &plic_irqdescs[pid];
}

static void plic_arch_irq_handle(void)
{
	struct irq_desc *desc;
	enum plic_irq_id pid;

	/* TODO: should consider multiple harts */
	pid = plic_read(PLIC_IRQ_CLAIM(0));
	if (unlikely(pid >= __NR_PLIC_IRQ))
		exit(-EINVAL); /* should not end here */

	desc = &plic_irqdescs[pid];

	/* execute irq handler */
	desc->action.irq_handler(desc->action.priv);

	plic_write(PLIC_IRQ_COMPL(0), pid);
}

int plic_init(void)
{
	struct irq_desc *desc;
	u32 i;

	/* setup irq descriptors */
	for (i = 0; i < __NR_PLIC_IRQ; i++) {
		desc = &plic_irqdescs[i];
		desc->id = i + __PLIC_IRQ_ID_OFS;
	}

	/* set interrupt threshold to 0 to allow all interrupts */
	/* TODO: need to consider multiple harts */
	plic_write(PLIC_IRQ_THRES(0), 0);

	set_arch_irq_handler(plic_arch_irq_handle);

	return register_irqchip(IRQCHIP_PLIC, &plic);
}
