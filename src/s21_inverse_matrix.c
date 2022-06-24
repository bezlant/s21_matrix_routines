#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
    if (A->rows != A->columns)
        return CALC_ERROR;

    double d = s21_determinant(A);
    if (fabs(d) < 1e-6)
        return CALC_ERROR;

    matrix_t adj = {0};
    s21_create_matrix(A->rows, A->columns, &adj);
    adjoint_inverse(A, &adj);

    int size = A->rows;

    if (s21_create_matrix(size, size, result) != OK)
        return MALLOC_FAILED;

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            result->matrix[i][j] = adj.matrix[i][j] / d;

    s21_remove_matrix(&adj);
    return OK;
}

void adjoint_inverse(matrix_t *A, matrix_t *result) {
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
            result->matrix[j][i] = sign * det(tmp, size - 1);
            sign = -sign;
        }
    }
    for (int i = 0; i < size; i++)
        free(tmp[i]);
    free(tmp);
}
