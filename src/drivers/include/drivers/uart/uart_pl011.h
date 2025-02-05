#ifndef _UART_PL011_H_
#define _UART_PL011_H_

#include <bits.h>

#define UART_DR				0x000
#define UART_RSR			0x004
#define UART_ECR			0x004
#define UART_FR				0x018
#define UART_ILPR			0x020
#define UART_IBRD			0x024
#define UART_FBRD			0x028
#define UART_LCR_H			0x02C
#define UART_CR				0x030
#define UART_IFLS			0x034
#define UART_IMSC			0x038
#define UART_RIS			0x03C
#define UART_MIS			0x040
#define UART_ICR			0x044
#define UART_DMACR			0x048
#define UART_PERIPH_ID0			0xFE0
#define UART_PERIPH_ID1			0xFE4
#define UART_PERIPH_ID2			0xFE8
#define UART_PERIPH_ID3			0xFEC
#define UART_CELL_ID0			0xFF0
#define UART_CELL_ID1			0xFF4
#define UART_CELL_ID2			0xFF8
#define UART_CELL_ID3			0xFFC

/* UART_DR */
#define UART_DR_DATA_MASK		0xFF
#define UART_DR_DATA_SHIFT		0
#define UART_DR_FE			BIT(8)
#define UART_DR_PE			BIT(9)
#define UART_DR_BE			BIT(10)
#define UART_DR_OE			BIT(11)

/* UART_FR */
#define UART_FR_CTS			BIT(0)
#define UART_FR_DSR			BIT(1)
#define UART_FR_DCD			BIT(2)
#define UART_FR_BUSY			BIT(3)
#define UART_FR_RXFE			BIT(4)
#define UART_FR_TXFF			BIT(5)
#define UART_FR_RXFF			BIT(6)
#define UART_FR_TXFE			BIT(7)
#define UART_FR_RI			BIT(8)

/* UART_IBRD */
#define UART_IBRD_BAUDDIVINT_MASK	0xFFFF
#define UART_IBRD_BAUDDIVINT_SHIFT	0

/* UART_FBRD */
#define UART_FBRD_BAUD_DIVFRAC_MASK	0x3F
#define UART_FBRD_BAUD_DIVFRAC_SHIFT	0

/* UART_LCR_H */
#define UART_LCR_H_BRK			BIT(0)
#define UART_LCR_H_PEN			BIT(1)
#define UART_LCR_H_EPS			BIT(2)
#define UART_LCR_H_STP2			BIT(3)
#define UART_LCR_H_FEN			BIT(4)
#define UART_LCR_H_WLEN_MASK		0x3
#define UART_LCR_H_WLEN_SHIFT		5
#define UART_LCR_H_SPS			BIT(7)

/* UART_CR */
#define UART_CR_UARTEN			BIT(0)
#define UART_CR_SIREN			BIT(1)
#define UART_CR_SIRLP			BIT(2)
#define UART_CR_LBE			BIT(7)
#define UART_CR_TXE			BIT(8)
#define UART_CR_RXE			BIT(9)
#define UART_CR_DTR			BIT(10)
#define UART_CR_RTS			BIT(11)
#define UART_CR_OUT1			BIT(12)
#define UART_CR_OUT2			BIT(13)
#define UART_CR_RTSEN			BIT(14)
#define UART_CR_CTSEN			BIT(15)

/* UART_DMACR */
#define UART_DMACR_RXDMAEN		BIT(0)
#define UART_DMACR_TXDMAEN		BIT(1)
#define UART_DMACR_DMAONERR		BIT(2)

enum uart_pl011_irq {
	UART_PL011_IRQ_RIM = 0,
	UART_PL011_IRQ_CTSM,
	UART_PL011_IRQ_DCDM,
	UART_PL011_IRQ_DSRM,
	UART_PL011_IRQ_RX,
	UART_PL011_IRQ_TX = 5,
	UART_PL011_IRQ_RT,
	UART_PL011_IRQ_FE,
	UART_PL011_IRQ_PE,
	UART_PL011_IRQ_BE,
	UART_PL011_IRQ_OE = 10,
};

enum uart_pl011_word_len {
	UART_PL011_WORD_LEN_5,
	UART_PL011_WORD_LEN_6,
	UART_PL011_WORD_LEN_7,
	UART_PL011_WORD_LEN_8,
};

enum uart_pl011_parity {
	UART_PL011_PARITY_DISABLE,
	UART_PL011_PARITY_ENABLE,
};

enum uart_pl011_stop_bit {
	UART_PL011_STOP_BIT_1,
	UART_PL011_STOP_BIT_2,
};

#if defined(CONFIG_UART_PL011)
int uart_pl011_puts(const char *s);
int uart_pl011_init(void);
#else /* !defined(CONFIG_UART_PL011) */
static inline int uart_pl011_puts(const char *s)
{
	return 0;
}

static inline int uart_pl011_init(void)
{
	return 0;
}
#endif /* defined(CONFIG_UART_PL011) */
#endif /* _UART_PL011_H_ */
