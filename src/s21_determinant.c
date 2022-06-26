#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
    if (!is_correct(A) || !result)
        return INCORRECT_MATRIX;

    if (A->rows != A->columns)
        return CALC_ERROR;

    if (A->rows == 1)
        *result = A->matrix[0][0];
    else
        *result = det(A->matrix, A->rows);

    return OK;
}
