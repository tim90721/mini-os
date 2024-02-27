#ifndef _STDIO_H_
#define _STDIO_H_

int __write(const char *s) __attribute__((weak));
int printf(const char *fmt, ...);
#endif /* _STDIO_H_ */
