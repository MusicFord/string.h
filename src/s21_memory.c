#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size n) {
  if (str == S21_NULL) {
    return S21_NULL;
  }

  const unsigned char *bytes = (const unsigned char *)str;
  const unsigned char target = (unsigned char)c;

  for (s21_size i = 0; i < n; ++i) {
    if (bytes[i] == target) {
      return (void *)(bytes + i);
    }
  }

  return S21_NULL;
}

int s21_memcmp(const void *str1, const void *str2, s21_size n) {
  if (n == 0) {
    return 0;
  }
  if (str1 == S21_NULL || str2 == S21_NULL) {
    return 0;
  }

  const unsigned char *left = (const unsigned char *)str1;
  const unsigned char *right = (const unsigned char *)str2;

  for (s21_size i = 0; i < n; ++i) {
    if (left[i] != right[i]) {
      return (int)left[i] - (int)right[i];
    }
  }

  return 0;
}

void *s21_memcpy(void *dest, const void *src, s21_size n) {
  if (n == 0) {
    return dest;
  }
  if (dest == S21_NULL || src == S21_NULL) {
    return dest;
  }

  unsigned char *destination = (unsigned char *)dest;
  const unsigned char *source = (const unsigned char *)src;

  for (s21_size i = 0; i < n; ++i) {
    destination[i] = source[i];
  }

  return dest;
}

void *s21_memset(void *str, int c, s21_size n) {
  if (str == S21_NULL) {
    return S21_NULL;
  }

  unsigned char *bytes = (unsigned char *)str;
  const unsigned char value = (unsigned char)c;

  for (s21_size i = 0; i < n; ++i) {
    bytes[i] = value;
  }

  return str;
}