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

bool is_legal(const matrix_t *const A, const matrix_t *const B) {
    if (A->matrix_type == INCORRECT_MATRIX ||
        B->matrix_type == INCORRECT_MATRIX)
        return false;
    if (A->rows != B->rows || A->cols != B->cols)
        return false;
    if (!A->rows || !A->cols || !B->rows || !B->cols)
        return false;

    return true;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    if (!is_legal(A, B))
        return FAILURE;

    for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < A->cols; j++)
            if (fabs(A->matrix[i][j] - B->matrix[i][j]) < 1e-06)
                return FAILURE;

    return SUCCESS;
}

matrix_t s21_sum_matrix(matrix_t *A, matrix_t *B);
matrix_t s21_sub_matrix(matrix_t *A, matrix_t *B);
