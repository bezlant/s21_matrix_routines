#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
    if (!is_correct(A))
        return INCORRECT_MATRIX;

    if (A->rows != A->columns || A->rows == 1)
        return CALC_ERROR;

    if (s21_create_matrix(A->columns, A->rows, result) != OK)
        return MALLOC_FAILED;

    adjoint(A, result);
    return OK;
}
