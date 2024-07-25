#include <compiler.h>
#include <errno.h>
#include <stddef.h>

#include <irq.h>
#include <interrupt.h>
#include <types.h>

static struct irq_chip *irqchips[__NR_IRQCHIP];
void (*arch_irq_handler)(void);
void (*arch_timer_handler)(void);

int unused_irq_handler(void *priv)
{
	return -EINVAL;
}

int set_arch_timer_handler(void (*timer_handler)(void))
{
	if (unlikely(!timer_handler))
		return -ENODEV;

	if (unlikely(arch_irq_handler))
		return -EBUSY;

	arch_timer_handler = timer_handler;

	return 0;
}

int set_arch_irq_handler(void (*irq_handler)(void))
{
	if (unlikely(!irq_handler))
		return -ENODEV;

	if (unlikely(arch_irq_handler))
		return -EBUSY;

	arch_irq_handler = irq_handler;

	return 0;
}

struct irq_desc *irq_desc_get(enum irqchip_id chip_id, enum irq_id irq_id)
{
	if (unlikely(irq_id >= __NR_IRQ || chip_id >= __NR_IRQCHIP))
		return NULL;

	if (unlikely(!irqchips[chip_id] || !irqchips[chip_id]->irq_desc_get))
		return NULL;

	return irqchips[chip_id]->irq_desc_get(irq_id);
}

static inline int irq_desc_sanity_check(struct irq_desc *desc)
{
	if (unlikely(!desc || !desc->chip))
		return -ENODEV;

	return 0;
}

int irq_disable(struct irq_desc *desc)
{
	int ret = irq_desc_sanity_check(desc);

	ret = irq_desc_sanity_check(desc);
	if (unlikely(ret))
		return ret;

	if (unlikely(!desc->chip || !desc->chip->irq_enable))
		return -ENODEV;

	if (desc->en_cnt == 0)
		return 0;

	if (--desc->en_cnt == 0) {
		ret = desc->chip->irq_enable(desc, false);
		if (ret) {
			desc->en_cnt++;
			return ret;
		}
	}

	return 0;
}

int irq_enable(struct irq_desc *desc)
{
	int ret;

	ret = irq_desc_sanity_check(desc);
	if (unlikely(ret))
		return ret;

	if (unlikely(!desc->chip || !desc->chip->irq_enable))
		return -ENODEV;

	if (desc->en_cnt) {
		desc->en_cnt++;
		return 0;
	}

	ret = desc->chip->irq_enable(desc, true);
	if (ret)
		return ret;

	desc->en_cnt++;

	return 0;
}

int irq_set_priority(struct irq_desc *desc, u32 priority)
{
	if (unlikely(!desc || !desc->chip || !desc->chip->irq_set_priority))
		return -ENODEV;

	return desc->chip->irq_set_priority(desc, priority);
}

int request_irq(struct irq_desc *desc, int (*irq_handler)(void *priv), void *priv)
{
	if (unlikely(!desc))
		return -ENODEV;

	if (unlikely(desc->action.irq_handler != unused_irq_handler))
		return -EBUSY;

	desc->action.irq_handler = irq_handler;
	desc->action.priv = priv;

	return 0;
}

void free_irq(struct irq_desc *desc)
{
	if (unlikely(!desc))
		return;

	if (unlikely(desc->action.irq_handler == unused_irq_handler))
		return;

	desc->action.irq_handler = unused_irq_handler;
	desc->action.priv = NULL;
}

int register_irqchip(enum irqchip_id id, struct irq_chip *chip)
{
	if (unlikely(id >= __NR_IRQCHIP))
		return -EINVAL;

	irqchips[id] = chip;

	return 0;
}

void unregister_irqchip(enum irqchip_id id, struct irq_chip *chip)
{
	if (unlikely(id >= __NR_IRQCHIP))
		return;

	/*
	 * check the registered irqchip slot is belonged to the chip that is
	 * going to be unregistered or not
	 */
	if (irqchips[id] != chip)
		return;

	irqchips[id] = NULL;
}
