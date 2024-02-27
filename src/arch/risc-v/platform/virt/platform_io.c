#include <stdio.h>

#include <drivers/uart/uart_16550A.h>

int __write(const char *s)
{
	return uart_puts(s);
}
