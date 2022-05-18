#include "test_s21_matrix.h"

START_TEST(create_matrix) {
    const int rows = 10;
    const int cols = 10;
    matrix_t *m = s21_create_matrix(rows, cols);
    double mtx[10][10] = {0};
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            ck_assert_ldouble_eq(mtx[i][j], m->matrix[i][j]);
        }
    }
    ck_assert_int_eq(m->rows, rows);
    ck_assert_int_eq(m->cols, cols);
    ck_assert_int_eq(m->matrix_type, ZERO_MATRIX);
    s21_remove_matrix(m);
}
END_TEST

Suite *suite_s21_create_matrix(void) {
    Suite *s = suite_create("suite_s21_create_matrix");
    TCase *tc = tcase_create("s21_create_matrix");

    tcase_add_test(tc, create_matrix);

    suite_add_tcase(s, tc);
    return s;
}
