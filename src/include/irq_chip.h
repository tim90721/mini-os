#ifndef _IRQ_CHIP_H_
#define _IRQ_CHIP_H_

#include <stdbool.h>
#include <stdint.h>

#include <platform/irq.h>

enum irq_id;
enum irqchip_id;
struct irq_desc;

struct irq_chip {
	int (*irq_enable)(struct irq_desc *desc, bool en);
	int (*irq_set_priority)(struct irq_desc *desc, u32 priority);
	struct irq_desc *(*irq_desc_get)(enum irq_id id);
};

int register_irqchip(enum irqchip_id id, struct irq_chip *chip);
void unregister_irqchip(enum irqchip_id id, struct irq_chip *chip);
#endif /* _IRQ_CHIP_H_ */
