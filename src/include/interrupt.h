#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

#include <irq.h>

extern void (*arch_irq_handler)(void);

int unused_irq_handler(void *priv);
int set_arch_irq_handler(void (*irq_handler)(void));
#endif /* _INTERRUPT_H_ */
