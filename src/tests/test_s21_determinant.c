#include "test_s21_matrix.h"

START_TEST(determinant1) {
    const int size = 5;
    matrix_t m = {0};
    s21_create_matrix(size, size, &m);

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            m.matrix[i][j] = j;

    ck_assert_double_eq_tol(s21_determinant(&m), 0, 1e-6);

    s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant2) {
    const int size = 4;
    matrix_t m = {0};
    s21_create_matrix(size, size, &m);

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            m.matrix[i][j] = j + i;

    ck_assert_double_eq_tol(s21_determinant(&m), 0, 1e-6);

    s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant3) {
    const int size = 5;
    matrix_t m = {0};
    s21_create_matrix(size, size, &m);
    m.matrix[0][1] = 6;
    m.matrix[0][2] = -2;
    m.matrix[0][3] = -1;
    m.matrix[0][4] = 5;
    m.matrix[1][3] = -9;
    m.matrix[1][4] = -7;
    m.matrix[2][1] = 15;
    m.matrix[2][2] = 35;
    m.matrix[3][1] = -1;
    m.matrix[3][2] = -11;
    m.matrix[3][3] = -2;
    m.matrix[3][4] = 1;
    m.matrix[4][0] = -2;
    m.matrix[4][1] = -2;
    m.matrix[4][2] = 3;
    m.matrix[4][4] = -2;

    ck_assert_double_eq_tol(s21_determinant(&m), 2480, 1e-6);

    s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant4) {
    const int size = 3;
    matrix_t m = {0};
    s21_create_matrix(size, size, &m);
    m.matrix[0][0] = 2;
    m.matrix[0][1] = 3;
    m.matrix[0][2] = 1;
    m.matrix[1][0] = 7;
    m.matrix[1][1] = 4;
    m.matrix[1][2] = 1;
    m.matrix[2][0] = 9;
    m.matrix[2][1] = -2;
    m.matrix[2][2] = 1;

    ck_assert_double_eq_tol(s21_determinant(&m), -32, 1e-6);

    s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant5) {
    const int size = 2;
    matrix_t m = {0};
    s21_create_matrix(size, size, &m);
    m.matrix[0][0] = -5;
    m.matrix[0][1] = -4;
    m.matrix[1][0] = -2;
    m.matrix[1][1] = -3;

    ck_assert_double_eq_tol(s21_determinant(&m), 7, 1e-6);

    s21_remove_matrix(&m);
}
END_TEST

Suite *suite_s21_determinant(void) {
    Suite *s = suite_create("suite_s21_determinant");
    TCase *tc = tcase_create("s21_determinant");

    tcase_add_test(tc, determinant1);
    tcase_add_test(tc, determinant2);
    tcase_add_test(tc, determinant3);
    tcase_add_test(tc, determinant4);
    tcase_add_test(tc, determinant5);

    suite_add_tcase(s, tc);
    return s;
}