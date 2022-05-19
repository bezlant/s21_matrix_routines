#ifndef TEST
#define TEST

#include "../s21_matrix.h"
#include <check.h>
#include <stdlib.h>
#include <time.h>

Suite *suite_s21_eq_matrix(void);
Suite *suite_s21_create_matrix(void);
void run_tests(void);
void run_testcase(Suite *testcase);

double get_rand(double min, double max);
#endif  //  TEST
