#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
    if (!is_correct(A))
        return INCORRECT_MATRIX;

    if (A->rows != A->columns)
        return CALC_ERROR;

    double d = 0;
    int code = s21_determinant(A, &d);

    if (fabs(d) < 1e-6 || code)
        return CALC_ERROR;
    if (A->rows == 1) {
        if (!s21_create_matrix(A->rows, A->rows, result)) {
            result->matrix[0][0] = 1.0 / A->matrix[0][0];
            return OK;
        } else {
            return MALLOC_FAILED;
        }
    }

    matrix_t complements = {0};

    int err = s21_calc_complements(A, &complements);
    if (err)
        return err;

    err = s21_transpose(&complements, result);
    if (err)
        return MALLOC_FAILED;

    int size = A->rows;

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            result->matrix[i][j] = result->matrix[i][j] / d;

    s21_remove_matrix(&complements);
    return OK;
}
