#ifndef _ARCH_IRQ_H_
#define _ARCH_IRQ_H_

#define arch_disable_irq()			\
	__asm__ __volatile__(			\
		"msr DAIFSet, #0xF"		\
	);

#define arch_enable_irq()			\
	__asm__ __volatile__(			\
		"msr DAIFClr, #0xF"		\
	);
#endif /* _ARCH_IRQ_H_ */
