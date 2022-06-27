#include "s21_matrix.h"

int is_correct(matrix_t *A) {
    return A && A->rows > 0 && A->columns > 0;
}

double det(double **m, int size) {
    double res = 0;

    if (size == 1)
        return m[0][0];
    matrix_t tmp = {0};
    if (s21_create_matrix(size, size, &tmp))
        return MALLOC_FAILED;

    int sign = 1;
    for (int i = 0; i < size; i++) {
        get_cofactor(m, tmp.matrix, 0, i, size);
        res += sign * m[0][i] * det(tmp.matrix, size - 1);
        sign = -sign;
    }

    s21_remove_matrix(&tmp);
    return res;
}

void get_cofactor(double **m, double **tmp, int skip_row, int skip_col,
                  int size) {
    for (int i = 0, row = 0; row < size; row++) {
        for (int j = 0, col = 0; col < size; col++) {
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

void adjoint(matrix_t *A, matrix_t *result) {
    if (A->rows == 1) {
        result->matrix[0][0] = 1;
        return;
    }

    matrix_t tmp = {0};

    if (s21_create_matrix(A->rows, A->rows, &tmp))
        return;

    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            get_cofactor(A->matrix, tmp.matrix, i, j, A->rows);

            int sign = ((i + j) % 2 == 0) ? 1 : -1;

            result->matrix[i][j] = sign * det(tmp.matrix, A->rows - 1);
        }
    }

    s21_remove_matrix(&tmp);
}
