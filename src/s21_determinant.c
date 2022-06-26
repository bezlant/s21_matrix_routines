#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
    if (A->rows != A->columns)
        return CALC_ERROR;

    if (A->rows == 0) {
        *result = A->matrix[0][0];
        return OK;
    }

    *result = det(A->matrix, A->rows);
    return OK;
}

double det(double **m, int size) {
    double res = 0;

    if (size == 1)
        return m[0][0];

    double **tmp = malloc(sizeof(double *) * size);
    if (!tmp)
        exit(MALLOC_FAILED);

    for (int i = 0; i < size; i++) {
        tmp[i] = malloc(sizeof(double) * size);
        if (!tmp[i])
            exit(MALLOC_FAILED);
    }

    int sign = 1;
    for (int i = 0; i < size; i++) {
        get_cofactor(m, tmp, 0, i, size);
        res += sign * m[0][i] * det(tmp, size - 1);
        sign = -sign;
    }

    for (int i = 0; i < size; i++)
        free(tmp[i]);
    free(tmp);

    return res;
}

void get_cofactor(double **m, double **tmp, int skip_row, int skip_col,
                  int size) {
    int i = 0;
    int j = 0;
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (row != skip_row && col != skip_col) {
                tmp[i][j] = m[row][col];
                j++;
                if (j == size - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}
