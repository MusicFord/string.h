#include <check.h>
#include <limits.h>
#include <stddef.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_memchr_finds_first_matching_byte) {
  const unsigned char data[] = {0x10, 0x80, 0xFF, 0x80, 0x00};
  ck_assert_ptr_eq(s21_memchr(data, 0x80, sizeof(data)),
                   memchr(data, 0x80, sizeof(data)));
}
END_TEST

START_TEST(test_memchr_does_not_read_past_n) {
  const unsigned char data[] = {0x11, 0x22, 0x33};
  ck_assert_ptr_eq(s21_memchr(data, 0x33, 2), memchr(data, 0x33, 2));
}
END_TEST

START_TEST(test_memchr_can_find_zero_byte) {
  const unsigned char data[] = {0x11, 0x00, 0x22};
  ck_assert_ptr_eq(s21_memchr(data, 0, sizeof(data)),
                   memchr(data, 0, sizeof(data)));
}
END_TEST

START_TEST(test_memchr_zero_length) {
  const unsigned char data[] = {0x11, 0x22};
  ck_assert_ptr_eq(s21_memchr(data, 0x11, 0), memchr(data, 0x11, 0));
}
END_TEST

START_TEST(test_memcmp_equal_data) {
  const unsigned char first[] = {0x00, 0x80, 0xFF, 0x2A};
  const unsigned char second[] = {0x00, 0x80, 0xFF, 0x2A};
  ck_assert_int_eq(s21_memcmp(first, second, sizeof(first)),
                   memcmp(first, second, sizeof(first)));
}
END_TEST

START_TEST(test_memcmp_compares_as_unsigned_bytes) {
  const unsigned char first[] = {0x80};
  const unsigned char second[] = {0x7F};
  int actual = s21_memcmp(first, second, 1);
  int expected = memcmp(first, second, 1);
  ck_assert_msg((actual < 0) == (expected < 0) &&
                    (actual > 0) == (expected > 0),
                "memcmp results have different signs: %d vs %d", actual,
                expected);
}
END_TEST

START_TEST(test_memcmp_stops_at_first_difference) {
  const unsigned char first[] = {0x12, 0x11, 0xFF};
  const unsigned char second[] = {0x12, 0x22, 0x00};
  int actual = s21_memcmp(first, second, sizeof(first));
  int expected = memcmp(first, second, sizeof(first));
  ck_assert_msg((actual < 0) == (expected < 0) &&
                    (actual > 0) == (expected > 0),
                "memcmp results have different signs: %d vs %d", actual,
                expected);
}
END_TEST

START_TEST(test_memcmp_zero_length) {
  const unsigned char first[] = {1};
  const unsigned char second[] = {2};
  ck_assert_int_eq(s21_memcmp(first, second, 0), memcmp(first, second, 0));
}
END_TEST

START_TEST(test_memcpy_copies_exact_number_of_bytes) {
  const unsigned char source[] = {0x00, 0x7F, 0x80, 0xFF};
  unsigned char actual[sizeof(source)] = {0};
  unsigned char expected[sizeof(source)] = {0};

  ck_assert_ptr_eq(s21_memcpy(actual, source, sizeof(source)), actual);
  memcpy(expected, source, sizeof(source));
  ck_assert_int_eq(memcmp(actual, expected, sizeof(actual)), 0);
}
END_TEST

START_TEST(test_memcpy_does_not_overwrite_bytes_after_n) {
  const unsigned char source[] = {1, 2, 3};
  unsigned char actual[] = {9, 9, 9, 9};
  unsigned char expected[] = {9, 9, 9, 9};

  s21_memcpy(actual, source, 2);
  memcpy(expected, source, 2);
  ck_assert_int_eq(memcmp(actual, expected, sizeof(actual)), 0);
}
END_TEST

START_TEST(test_memcpy_zero_length) {
  const unsigned char source[] = {1, 2};
  unsigned char actual[] = {3, 4};
  ck_assert_ptr_eq(s21_memcpy(actual, source, 0), actual);
  ck_assert_int_eq(actual[0], 3);
  ck_assert_int_eq(actual[1], 4);
}
END_TEST

START_TEST(test_memset_fills_exact_number_of_bytes) {
  unsigned char actual[] = {1, 2, 3, 4, 5};
  unsigned char expected[] = {1, 2, 3, 4, 5};

  ck_assert_ptr_eq(s21_memset(actual, 0xAB, 3), actual);
  memset(expected, 0xAB, 3);
  ck_assert_int_eq(memcmp(actual, expected, sizeof(actual)), 0);
}
END_TEST

START_TEST(test_memset_converts_value_to_unsigned_byte) {
  unsigned char actual[3] = {0};
  unsigned char expected[3] = {0};
  const int value = UCHAR_MAX + 2;

  s21_memset(actual, value, sizeof(actual));
  memset(expected, value, sizeof(expected));
  ck_assert_int_eq(memcmp(actual, expected, sizeof(actual)), 0);
}
END_TEST

START_TEST(test_memset_zero_length) {
  unsigned char actual[] = {5, 6};
  ck_assert_ptr_eq(s21_memset(actual, 0, 0), actual);
  ck_assert_int_eq(actual[0], 5);
  ck_assert_int_eq(actual[1], 6);
}
END_TEST

static Suite *memory_suite(void) {
  Suite *suite = suite_create("s21_memory");
  TCase *test_case = tcase_create("memory_functions");

  tcase_add_test(test_case, test_memchr_finds_first_matching_byte);
  tcase_add_test(test_case, test_memchr_does_not_read_past_n);
  tcase_add_test(test_case, test_memchr_can_find_zero_byte);
  tcase_add_test(test_case, test_memchr_zero_length);
  tcase_add_test(test_case, test_memcmp_equal_data);
  tcase_add_test(test_case, test_memcmp_compares_as_unsigned_bytes);
  tcase_add_test(test_case, test_memcmp_stops_at_first_difference);
  tcase_add_test(test_case, test_memcmp_zero_length);
  tcase_add_test(test_case, test_memcpy_copies_exact_number_of_bytes);
  tcase_add_test(test_case, test_memcpy_does_not_overwrite_bytes_after_n);
  tcase_add_test(test_case, test_memcpy_zero_length);
  tcase_add_test(test_case, test_memset_fills_exact_number_of_bytes);
  tcase_add_test(test_case, test_memset_converts_value_to_unsigned_byte);
  tcase_add_test(test_case, test_memset_zero_length);

  suite_add_tcase(suite, test_case);
  return suite;
}

int main(void) {
  Suite *suite = memory_suite();
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  int failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return failed == 0 ? 0 : 1;
}
