#include <mmio.h>

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

	return 0;
}
