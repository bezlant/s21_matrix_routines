#include "test_s21_matrix.h"

START_TEST(empty) {
    matrix_t a = {0};
    matrix_t b = {0};
    ck_assert_int_eq(s21_calc_complements(&a, &b), INCORRECT_MATRIX);
}
END_TEST

START_TEST(size_mismatch) {
    matrix_t a = {0};
    matrix_t b = {0};
    s21_create_matrix(1, 2, &a);
    ck_assert_int_eq(s21_calc_complements(&a, &b), CALC_ERROR);
    s21_remove_matrix(&a);
}
END_TEST

START_TEST(complements) {
    const int size = 3;
    matrix_t m = {0};
    s21_create_matrix(size, size, &m);
    m.matrix[0][0] = 1;
    m.matrix[0][1] = 2;
    m.matrix[0][2] = 3;
    m.matrix[1][1] = 4;
    m.matrix[1][2] = 2;
    m.matrix[2][0] = 5;
    m.matrix[2][1] = 2;
    m.matrix[2][2] = 1;

    matrix_t expected = {0};
    s21_create_matrix(size, size, &expected);
    expected.matrix[0][1] = 10;
    expected.matrix[0][2] = -20;
    expected.matrix[1][0] = 4;
    expected.matrix[1][1] = -14;
    expected.matrix[1][2] = 8;
    expected.matrix[2][0] = -8;
    expected.matrix[2][1] = -2;
    expected.matrix[2][2] = 4;

    matrix_t res = {0};
    s21_calc_complements(&m, &res);

    ck_assert_int_eq(s21_eq_matrix(&expected, &res), SUCCESS);
    s21_remove_matrix(&m);
    s21_remove_matrix(&res);
    s21_remove_matrix(&expected);
}
END_TEST

Suite *suite_s21_calc_complements(void) {
    Suite *s = suite_create("suite_s21_calc_complements");
    TCase *tc = tcase_create("s21_calc_complements");

    tcase_add_test(tc, complements);
    tcase_add_test(tc, empty);
    tcase_add_test(tc, size_mismatch);

    suite_add_tcase(s, tc);
    return s;
}
