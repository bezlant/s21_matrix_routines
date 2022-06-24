#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
    if (s21_create_matrix(A->columns, A->rows, result) != OK)
        return MALLOC_FAILED;

    for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < A->columns; j++)
            result->matrix[j][i] = A->matrix[i][j];
    return OK;
}
