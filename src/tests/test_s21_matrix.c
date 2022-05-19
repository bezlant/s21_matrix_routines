#include "test_s21_matrix.h"

START_TEST(create_matrix) {
    const int rows = rand() % 1000;
    const int cols = rand() % 1000;
    matrix_t m;
    s21_create_matrix(rows, cols, &m);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            m.matrix[i][j] = 0;
            ck_assert_ldouble_eq_tol(0, m.matrix[i][j], 1e-06);
        }
    }
    ck_assert_int_eq(m.rows, rows);
    ck_assert_int_eq(m.columns, cols);
    s21_remove_matrix(&m);
}
END_TEST

START_TEST(no_rows) {
    const int rows = 0;
    const int cols = 10;
    matrix_t m;
    ck_assert_int_eq(s21_create_matrix(rows, cols, &m), INCORRECT_MATRIX);
}
END_TEST

START_TEST(no_cols) {
    const int rows = 10;
    const int cols = 0;

    matrix_t m;
    ck_assert_int_eq(s21_create_matrix(rows, cols, &m), INCORRECT_MATRIX);
}
END_TEST

Suite *suite_s21_create_matrix(void) {
    Suite *s = suite_create("suite_s21_create_matrix");
    TCase *tc = tcase_create("s21_create_matrix");

    tcase_add_loop_test(tc, create_matrix, 0, 100);
    tcase_add_test(tc, no_rows);
    tcase_add_test(tc, no_cols);

    suite_add_tcase(s, tc);
    return s;
}

START_TEST(eq_matrix) {
    const int rows = rand() % 1000;
    const int cols = rand() % 1000;
    matrix_t m;
    s21_create_matrix(rows, cols, &m);
    matrix_t mtx;
    s21_create_matrix(rows, cols, &mtx);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            double rand_val = get_rand(DBL_MIN, DBL_MAX);
            m.matrix[i][j] = rand_val;
            mtx.matrix[i][j] = rand_val;
        }
    }
    ck_assert_int_eq(s21_eq_matrix(&m, &mtx), SUCCESS);
    s21_remove_matrix(&m);
    s21_remove_matrix(&mtx);
}
END_TEST

START_TEST(not_eq) {
    const int rows = rand() % 1000;
    const int cols = rand() % 1000;
    matrix_t m;
    s21_create_matrix(rows, cols, &m);
    matrix_t mtx;
    s21_create_matrix(rows, cols, &mtx);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX) + 1;
            mtx.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
        }
    }
    ck_assert_int_eq(s21_eq_matrix(&m, &mtx), FAILURE);
    s21_remove_matrix(&m);
    s21_remove_matrix(&mtx);
}
END_TEST

Suite *suite_s21_eq_matrix(void) {
    Suite *s = suite_create("suite_s21_eq_matrix");
    TCase *tc = tcase_create("s21_eq_matrix");

    tcase_add_test(tc, not_eq);
    tcase_add_loop_test(tc, eq_matrix, 0, 100);

    suite_add_tcase(s, tc);
    return s;
}
