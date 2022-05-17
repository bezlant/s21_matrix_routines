#include "s21_matrix.h"

matrix_t *s21_create_matrix(const int rows, const int columns) {
    matrix_t *new = calloc(1, sizeof(matrix_t));
    new->rows = rows;
    new->cols = columns;
    new->matrix_type = ZERO_MATRIX;
    new->matrix = calloc(rows, sizeof(double *));
    for (int i = 0; i < rows; i++)
        new->matrix[i] = calloc(columns, sizeof(double));
    return new;
}

void s21_remove_matrix(matrix_t *const A) {
    for (int i = 0; i < A->rows; i++)
        free(A->matrix[i]);
    free(A->matrix);
    free(A);
}
