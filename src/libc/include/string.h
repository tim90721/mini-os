#ifndef _STRING_H_
#define _STRING_H_

#include <stdint.h>

void *memchr(const void *str, int c, size_t n);
int memcmp(const void *str1, const void *str2, size_t n);
void *memcpy(void *dst, const void *src, size_t n);
void *memmove(void *dst, const void *src, size_t n);
void *memset(void *str, int c, size_t n);

char *strcat(char *dst, const char *src);
char *strncat(char *dst, const char *src, size_t n);
char *strchr(const char *str, int c);
int strcmp(const char *str1, const char *str2);
int strncmp(const char *str1, const char *str2, size_t n);
int strcoll(const char *str1, const char *str2);
char *strcpy(char *dst, const char *src);
char *strncpy(char *dst, const char *src, size_t n);
size_t strcspn(const char *str1, const char *str2);
char *strerror(int errnum);
size_t strlen(const char *sttr);
char *strpbrk(const char *str1, const char *str2);
char *strrchr(const char *str, int c);
size_t strspn(const char *str1, const char *str2);
char *strstr(const char *haystack, const char *neeedle);
char *strtok(char *str, const char *delim);
size_t strxfrm(char *dst, const char *src, size_t n);
#endif /* _STRING_H_ */
