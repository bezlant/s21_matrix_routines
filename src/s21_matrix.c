#include "s21_matrix.h"

int s21_create_matrix(const int rows, const int columns, matrix_t *result) {
    if (rows <= 0 || columns <= 0)
        return INCORRECT_MATRIX;
    result->rows = rows;
    result->columns = columns;
    result->matrix = calloc(rows, sizeof(double *));
    for (int i = 0; i < rows; i++)
        result->matrix[i] = calloc(columns, sizeof(double));
    return OK;
}

void s21_remove_matrix(matrix_t *const A) {
    for (int i = 0; i < A->rows; i++)
        free(A->matrix[i]);
    free(A->matrix);
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < A->columns; j++)
            if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-07)
                return FAILURE;

    return SUCCESS;
}

matrix_t s21_sum_matrix(matrix_t *A, matrix_t *B);
matrix_t s21_sub_matrix(matrix_t *A, matrix_t *B);
