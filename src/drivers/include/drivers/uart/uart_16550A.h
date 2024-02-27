#ifndef _UART_16550A_H_
#define _UART_16550A_H_

#include <bits.h>

/* DLAB = 0 */
#define RHR			0x00 /* RO */
#define THR			0x00 /* WO */
#define IER			0x01
#define ISR			0x02 /* RO */
#define FCR			0x02 /* WO */
#define LCR			0x03
#define MCR			0x04
#define LSR			0x05
#define MSR			0x06
#define SPR			0x07

/* DLAB = 1 */
#define DLL			0x00
#define DLM			0x01
#define PSD			0x05 /* Pre-Scalar Division */

/* IER */
#define IER_RX_RDY_IRQ_EN	BIT(0)
#define IER_TX_EPT_IRQ_EN	BIT(1)
#define IER_LINE_STA_IRQ_EN	BIT(2)
#define IER_MD_STA_IRQ_EN	BIT(3)

/* LCR */
#define LCR_DLEN_MASK		0x3
#define LCR_DLEN_SHIFT		0
#define LCR_TWO_STOP_BITS	BIT(2)
#define LCR_PARITY_EN		BIT(3)
#define LCR_PARITY_EVEN_EN	BIT(4)
#define LCR_DLAB_EN		BIT(7)

/* LSR */
#define LSR_RX_RDY		BIT(0)
#define LSR_OVERRUN		BIT(1)
#define LSR_PARITY_ERR		BIT(2)
#define LSR_FRAME_ERR		BIT(3)
#define LSR_BRK			BIT(4)
#define LSR_TX_EPT		BIT(5)

#if defined(CONFIG_UART_16550A)
int uart_puts(const char *s);
int uart_init(void);
#else /* !defined(CONFIG_UART_16550A) */
static inline int uart_puts(const char *s)
{
	return 0;
}

static inline int uart_init(void)
{
	return 0;
}
#endif /* defined(CONFIG_UART_16550A) */
#endif /* _UART_16550A_H_ */
