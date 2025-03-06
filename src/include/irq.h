#ifndef _IRQ_H_
#define _IRQ_H_

#include <arch/irq.h>

#include <irq_chip.h>
#include <irq_desc.h>

#include <platform/irq.h>

enum irq_id;
enum irqchip_id;

struct irq_desc *irq_desc_get(enum irqchip_id chip, enum irq_id irq);

int irq_enable(struct irq_desc *desc);
int irq_disable(struct irq_desc *desc);
int irq_set_priority(struct irq_desc *desc, uint32_t priority);

int request_irq(struct irq_desc *desc, int (*irq_handler)(void *priv), void *priv);
void free_irq(struct irq_desc *desc);

static inline void disable_irq(void)
{
	arch_disable_irq();
}

static inline void enable_irq(void)
{
	arch_enable_irq();
}
#endif /* _IRQ_H_ */
