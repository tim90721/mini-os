#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#define GIC_BASE_DIST	0x08000000
#define GIC_BASE_CPU	0x08010000
#define GIC_BASE_V2M	0x08020000
#define GIC_BASE_HYP	0x08030000
#define GIC_BASE_VCPU	0x08040000
#define UART_BASE	0x09000000

int platform_init(void);
#endif /* _PLATFORM_H_ */
