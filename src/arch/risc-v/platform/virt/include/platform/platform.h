#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#define CLINT_BASE	0x02000000
#define PLIC_BASE	0x0C000000
#define UART_BASE	0x10000000

int platform_init(void);
#endif /* _PLATFORM_H_ */
