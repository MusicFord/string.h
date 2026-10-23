#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

// Проверка первого вхождения символа.
START_TEST(test_s21_strchr_first_occurrence) {
  char str[] = "hello";

  ck_assert_ptr_eq(s21_strchr(str, 'l'), strchr(str, 'l'));
  ck_assert_ptr_eq(s21_strchr(str, 'l'), &str[2]);
}
END_TEST

// Проверка поиска первого символа строки.
START_TEST(test_s21_strchr_first_character) {
  char str[] = "hello";

  ck_assert_ptr_eq(s21_strchr(str, 'h'), strchr(str, 'h'));
  ck_assert_ptr_eq(s21_strchr(str, 'h'), str);
}
END_TEST

// Проверка, если символ отсутствует.
START_TEST(test_s21_strchr_character_not_found) {
  char str[] = "hello";

  ck_assert_ptr_eq(s21_strchr(str, 'z'), strchr(str, 'z'));
  ck_assert_ptr_eq(s21_strchr(str, 'z'), NULL);
}
END_TEST

// Проверка поиска завершающего нулевого символа.
START_TEST(test_s21_strchr_null_terminator) {
  char str[] = "hello";

  ck_assert_ptr_eq(s21_strchr(str, '\0'), strchr(str, '\0'));
  ck_assert_ptr_eq(s21_strchr(str, '\0'), &str[5]);
}
END_TEST

// Проверка пустой строки.
START_TEST(test_s21_strchr_empty_string) {
  char str[] = "";

  ck_assert_ptr_eq(s21_strchr(str, '\0'), strchr(str, '\0'));
  ck_assert_ptr_eq(s21_strchr(str, 'a'), strchr(str, 'a'));
}
END_TEST

// Проверка строки с повторяющимися символами.
START_TEST(test_s21_strchr_repeated_character) {
  char str[] = "banana";

  ck_assert_ptr_eq(s21_strchr(str, 'a'), strchr(str, 'a'));
  ck_assert_ptr_eq(s21_strchr(str, 'a'), &str[1]);
}
END_TEST

// Проверка поиска символа с кодом 255.
START_TEST(test_s21_strchr_unsigned_character) {
  char str[] = {(char)0xFF, '\0'};

  ck_assert_ptr_eq(s21_strchr(str, 255), strchr(str, 255));
}
END_TEST

int main(void) {
  Suite *s = suite_create("s21_strchr");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_strchr_first_occurrence);
  tcase_add_test(tc_core, test_s21_strchr_first_character);
  tcase_add_test(tc_core, test_s21_strchr_character_not_found);
  tcase_add_test(tc_core, test_s21_strchr_null_terminator);
  tcase_add_test(tc_core, test_s21_strchr_empty_string);
  tcase_add_test(tc_core, test_s21_strchr_repeated_character);
  tcase_add_test(tc_core, test_s21_strchr_unsigned_character);

  suite_add_tcase(s, tc_core);

  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);

  int failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}