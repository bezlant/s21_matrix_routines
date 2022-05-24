#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
    if (A->rows != A->columns || result->rows != A->rows ||
        result->columns != A->columns)
        return CALC_ERROR;

    adjoint(A, result);
    return OK;
}

void adjoint(matrix_t *A, matrix_t *result) {
    if (A->rows == 1) {
        result->matrix[0][0] = 1;
        return;
    }

    int size = A->rows;
    double **tmp = malloc(sizeof(double *) * size);
    for (int i = 0; i < size; i++)
        tmp[i] = malloc(sizeof(double) * size);

    int sign = 1;
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            get_cofactor(A->matrix, tmp, i, j, size);
            result->matrix[i][j] = sign * det(tmp, size - 1);
            sign = -sign;
        }
    }
    for (int i = 0; i < size; i++)
        free(tmp[i]);
    free(tmp);
}
