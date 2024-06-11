#ifndef _IRQCHIP_PLIC_H_
#define _IRQCHIP_PLIC_H_

#include <platform/platform.h>

#define PLIC_IRQ_PRIORITY(irq)		(0x000000 + 0x4 * (irq))
#define PLIC_IRQ_PENDING(irq)		(0x001000 + 0x4 * ((irq) / 32))
#define PLIC_IRQ_ENABLE(cpu, irq)	(0x002000 + ((cpu) * 0x80) \
					 + 0x4 * ((irq) / 32))
#define PLIC_IRQ_THRES(cpu)		(0x200000 + 0x1000 * (cpu) + 0x0000)
#define PLIC_IRQ_CLAIM(cpu)		(0x200000 + 0x1000 * (cpu) + 0x0004)
#define PLIC_IRQ_COMPL(cpu)		(0x200000 + 0x1000 * (cpu) + 0x0004)

enum plic_irq_priority {
	PLIC_IRQ_PRIORITY_0,
	PLIC_IRQ_PRIORITY_1,
	PLIC_IRQ_PRIORITY_2,
	PLIC_IRQ_PRIORITY_3,
	PLIC_IRQ_PRIORITY_4,
	PLIC_IRQ_PRIORITY_5,
	PLIC_IRQ_PRIORITY_6,
	PLIC_IRQ_PRIORITY_7,

	__PLIC_IRQ_PRIORITY_MAX,
};

int plic_init(void);
#endif /* _IRQCHIP_PLIC_H_ */
