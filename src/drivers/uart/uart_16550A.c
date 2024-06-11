#include <errno.h>
#include <mmio.h>
#include <stddef.h>

#include <irq.h>

#include <drivers/uart/uart_16550A.h>

#include <platform/platform.h>

static inline void uart_write(u8 addr, u8 val)
{
	mmio_write_8(UART_BASE + addr, val);
}

static inline u8 uart_read(u8 addr)
{
	return mmio_read_8(UART_BASE + addr);
}

/* wait until UART Tx empty, then it is safe to Tx a character */
static void uart_putc(const char c)
{
	while (!(uart_read(LSR) & LSR_TX_EPT))
		;

	uart_write(THR, c);
}

int uart_puts(const char *s)
{
	int cnt = 0;

	while (*s) {
		uart_putc(*s++);
		cnt++;
	}

	return cnt;
}

static int uart_getc(void)
{
	if (uart_read(LSR) & LSR_RX_RDY)
		return uart_read(RHR);

	return -1;
}

static int uart_rx_isr(void *priv)
{
	int c;

	while ((c = uart_getc())) {
		if (c == -1)
			break;

		uart_putc((char)c);
		if ((char)c == '\r')
			uart_putc('\n');
	}

	return 0;
}

static inline int uart_irq_init(void)
{
	struct irq_desc *desc = irq_desc_get(IRQCHIP_PLIC, IRQ_UART_0);

	if (!desc)
		return -ENODEV;

	/* enable receive irq */
	uart_write(IER, uart_read(IER) | IER_RX_RDY_IRQ_EN);

	request_irq(desc, uart_rx_isr, NULL);
	irq_set_priority(desc, 1);
	irq_enable(desc);

	return 0;
}

int uart_init(void)
{
	u8 lcr;

	/* disable all irq */
	uart_write(IER, 0);

	/* setup baudrate */
	lcr = uart_read(LCR);
	uart_write(LCR, lcr | LCR_DLAB_EN);
	uart_write(DLL, 0x3);
	uart_write(DLM, 0);
	uart_write(LCR, lcr);

	/*
	 * setup data configuration
	 * data length = 8
	 * stop bit length = 1
	 * no parity
	 * no break;
	 */
	uart_write(LCR, (0x3 & LCR_DLEN_MASK) << LCR_DLEN_SHIFT);

	return uart_irq_init();
}
