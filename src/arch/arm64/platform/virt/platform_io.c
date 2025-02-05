#include <stdio.h>

#include <drivers/uart/uart_pl011.h>

int __write(const char *s)
{
	return uart_pl011_puts(s);
}
