#ifndef S21_STRING_H
#define S21_STRING_H

#include <stddef.h>

typedef size_t s21_size;

#ifndef S21_NULL
#define S21_NULL ((void *)0)
#endif

void *s21_memchr(const void *str, int c, s21_size n);
int s21_memcmp(const void *str1, const void *str2, s21_size n);
void *s21_memcpy(void *dest, const void *src, s21_size n);
void *s21_memset(void *str, int c, s21_size n);
char *s21_strchr(const char *str, int c);

#endif  // S21_STRING_H
