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

    matrix_t adj = {0};
    if (s21_calc_complements(A, &adj))
        return MALLOC_FAILED;

    matrix_t transposed = {0};

    if (s21_transpose(&adj, &transposed) ||
        s21_create_matrix(A->rows, A->rows, result))
        return MALLOC_FAILED;

    for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < A->rows; j++)
            result->matrix[i][j] = transposed.matrix[i][j] / d;

    s21_remove_matrix(&transposed);
    s21_remove_matrix(&adj);
    return OK;
}
