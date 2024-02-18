#include <errno.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define BUF_LEN		256

/*
 * fill the buffer at position (pos + ofs) with content c
 * after updating the buffer, pos is not updated
 */
static inline void __buffer_input(char *buf, u32 *pos, u32 ofs,
				  u32 size, char c)
{
	if (*pos + ofs < size)
		buf[*pos + ofs] = c;
}

/*
 * fill the buffer at position (pos) with content c
 * after updating the buffer, pos is automatically moving forward by 1
 */
static inline void buffer_input(char *buf, u32 *pos, u32 size, char c)
{
	__buffer_input(buf, pos, 0, size, c);
	(*pos)++;
}

/*
 * handle printf format %x
 */
static void buffer_input_hex(char *buf, u32 *pos, u32 size,
			     bool longarg, va_list args)
{
	long num = (longarg) ? va_arg(args, long) : va_arg(args, int);
	long n;
	int digits;
	int i;

	digits = ((longarg) ? sizeof(long) : sizeof(int)) * 2;
	for (i = 0; i < digits; i++) {
		n = ((num) >> (4 * i)) & 0xF;
		buffer_input(buf, pos, size,
			     (n < 10) ? (n + '0') : (n - 10 + 'a'));
	}
}

/*
 * handle printf format %d
 */
static void buffer_input_digits(char *buf, u32 *pos, u32 size,
				bool longarg, va_list args)
{
	long num = (longarg) ? va_arg(args, long) : va_arg(args, int);
	long n;
	int digits = 0;
	int i;

	if (num < 0) {
		buffer_input(buf, pos, size, '-');
		num = -num;
	}

	for (n = num; n /= num; digits++)
		;

	for (i = digits - 1; i >= 0; i--) {
		__buffer_input(buf, pos, i, size, num % 10);
		num /= 10;
	}

	(*pos) += digits;
}

/*
 * handle printf format string
 */
static inline void buffer_input_string(char *buf, u32 *pos, u32 size,
				       const char *s)
{
	while (*s)
		buffer_input(buf, pos, size, *s++);
}

/*
 * decode format character followed by a '%'
 * %x: print argument as hex value
 * %d: print argument as decimal value
 * %s: print argument as a string
 * %c: print argument as a character
 * %%: print argument as a %
 * Other formats are not supported yet
 * TODO: support %p, %u
 */
static int decode_format(char *buf, u32 *pos,
			 u32 size, const char *fmt, va_list args)
{
	const char *old_fmt = fmt;
	bool longarg = false;

	if (*fmt == 'l') {
		longarg = true;
		fmt++;
	}

	switch (*fmt) {
	case 'x':
		buffer_input_hex(buf, pos, size, longarg, args);
		longarg = 0;
		break;
	case 'd':
		buffer_input_digits(buf, pos, size, longarg, args);
		longarg = 0;
		break;
	case 's':
		buffer_input_string(buf, pos, size, va_arg(args, const char *));
		break;
	case 'c':
		buffer_input(buf, pos, size, va_arg(args, int));
		break;
	case '%':
		buffer_input(buf, pos, size, '%');
		break;
	default:
		return -EINVAL;
	}

	fmt++;

	return fmt - old_fmt;
}

static int vsnprintf(char *buf, u32 size, const char *fmt, va_list args)
{
	u32 pos = 0;
	u8 format = 0;
	int ret;

	while (*fmt) {
		if (*fmt == '%') {
			fmt++;
			format = 1;
		} else if (format) {
			ret = decode_format(buf, &pos, size, fmt, args);
			if (ret < 0)
				return 0;

			fmt += ret;
			format = 0;
		} else {
			if (pos < size)
				buf[pos] = *fmt++;
			pos++;
		}
	}

	if (pos < size)
		buf[pos] = '\0';
	else
		buf[size - 1] = '\0';

	return pos;
}

static int vscnprintf(char *buf, u32 size, const char *fmt, va_list args)
{
	u32 done;

	if (size == 0)
		return 0;

	done = vsnprintf(buf, size, fmt, args);
	if (done < size)
		return done;

	return size - 1;
}

static int vprintf(const char *fmt, va_list args)
{
	char buf[BUF_LEN];
	u32 done;

	done = vscnprintf(buf, BUF_LEN, fmt, args);
	if (done == 0)
		return done;

	/* TODO: call customized write functions */

	return done;
}

int printf(const char *fmt, ...)
{
	va_list args;
	int done;

	va_start(args, fmt);
	done = vprintf(fmt, args);
	va_end(args);

	return done;
}
