#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  const unsigned char *current = (const unsigned char *)str;
  unsigned char target = (unsigned char)c;

  while (*current != '\0') {
    if (*current == target) {
      return (char *)current;
    }
    current++;
  }

  if (target == '\0') {
    return (char *)current;
  }

  return S21_NULL;
}