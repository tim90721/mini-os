#include <errno.h>
#include <mmio.h>
#include <stdbool.h>
#include <stddef.h>

#include <drivers/uart/uart_pl011.h>

#include <platform/platform.h>

struct uart_device {
	u32 clock;
	u32 baudrate;
	u8 word_len;
	u8 stopbit;
	u8 parity;
};

struct uart_device uart_default_dev = {
	.clock = 24000000,
	.baudrate = 115200,
	.word_len = UART_PL011_WORD_LEN_8,
	.stopbit = UART_PL011_STOP_BIT_1,
	.parity = UART_PL011_PARITY_DISABLE,
};

static inline void uart_write(u32 addr, u32 val)
{
	mmio_write_32(UART_BASE + addr, val);
}

static inline u32 uart_read(u32 addr)
{
	return mmio_read_32(UART_BASE + addr);
}

static inline void uart_pl011_wait_tx_complete(void)
{
	while (uart_read(UART_FR) & UART_FR_BUSY)
		;
}

static void uart_pl011_putc(const char c)
{
	while (!(uart_read(UART_FR) & UART_FR_TXFE))
		;

	uart_write(UART_DR, c);
}

int uart_pl011_puts(const char *s)
{
	int cnt = 0;

	while (*s) {
		uart_pl011_putc(*s++);
		cnt++;
	}

	return cnt;
}

static void uart_pl011_enable(bool en)
{
	u32 val = uart_read(UART_CR);

	val = (val & (~(UART_CR_UARTEN)));
	if (en)
		val |= UART_CR_UARTEN;

	uart_write(UART_CR, val);
}

static void uart_pl011_tx_enable(bool en)
{
	u32 val = uart_read(UART_CR);

	val = (val & (~(UART_CR_TXE)));
	if (en)
		val |= UART_CR_TXE;

	uart_write(UART_CR, val);
}

static void uart_pl011_fifo_enable(bool en)
{
	u32 val = uart_read(UART_LCR_H);

	val = (val & (~(UART_LCR_H_FEN)));
	if (en)
		val |= UART_LCR_H_FEN;

	uart_write(UART_LCR_H, val);
}

static void uart_pl011_baudrate_config(struct uart_device *udev)
{
	u32 div = 4 * udev->clock / udev->baudrate;

	uart_write(UART_FBRD, div & 0x3F);
	uart_write(UART_IBRD, (div >> 6) & 0xFFFF);
}

static void uart_pl011_frame_config(struct uart_device *udev)
{
	/* FIXME: disable all default configuration first */
	u32 val = 0;

	if (udev->parity)
		val |= UART_LCR_H_PEN;
	if (udev->stopbit)
		val |= UART_LCR_H_STP2;

	val |= (udev->word_len & UART_LCR_H_WLEN_MASK) << UART_LCR_H_WLEN_SHIFT;

	uart_write(UART_LCR_H, val);
}

int uart_pl011_init(void)
{
	/* 1. Disable UART */
	uart_pl011_enable(0);
	/* FIXME: disable all features first */
	uart_write(UART_CR, 0);

	/* 2. Wait for current data transmit complete */
	uart_pl011_wait_tx_complete();

	/* 3. Flush FIFO */
	uart_pl011_fifo_enable(0);

	/* 4. Configure */
	/* 4.1 Configure baudrate */
	uart_pl011_baudrate_config(&uart_default_dev);

	/* 4.2 Configure data frame */
	uart_pl011_frame_config(&uart_default_dev);

	/* 4.3 Enable Tx */
	uart_pl011_tx_enable(1);

	/* 5. Enable UART */
	uart_pl011_enable(1);

	return 0;
}
