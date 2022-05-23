#include "s21_matrix.h"

int s21_create_matrix(const int rows, const int columns, matrix_t *result) {
    if (rows <= 0 || columns <= 0)
        return INCORRECT_MATRIX;
    result->rows = rows;
    result->columns = columns;
    result->matrix = calloc(rows, sizeof(double *));
    if (!result->matrix)
        return MALLOC_FAILED;
    for (int i = 0; i < rows; i++) {
        result->matrix[i] = calloc(columns, sizeof(double));
        if (!result->matrix[i])
            return MALLOC_FAILED;
    }
    return OK;
}

void s21_remove_matrix(matrix_t *const A) {
    for (int i = 0; i < A->rows; i++)
        free(A->matrix[i]);
    free(A->matrix);
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    if (A->rows != B->rows || A->columns != B->columns)
        return CALC_ERROR;
    for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < A->columns; j++)
            if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-07)
                return FAILURE;

    return SUCCESS;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    if (A->rows != B->rows || A->columns != B->columns)
        return CALC_ERROR;
    for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < A->columns; j++)
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];

    return OK;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    if (A->rows != B->rows || A->columns != B->columns)
        return CALC_ERROR;
    for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < A->columns; j++)
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];

    return OK;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
    if (result->rows != A->rows || result->columns != A->columns)
        return CALC_ERROR;
    for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < A->columns; j++)
            result->matrix[i][j] = A->matrix[i][j] * number;
    return OK;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    if ((A->columns != B->rows) || (A->rows != B->columns))
        return CALC_ERROR;
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
            result->matrix[i][j] = 0;
            for (int k = 0; k < A->columns; k++)
                result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
    }
    return OK;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
    if (result->rows != A->columns || result->columns != A->rows)
        return CALC_ERROR;

    for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < A->columns; j++)
            result->matrix[j][i] = A->matrix[i][j];
    return OK;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
    if (A->rows != A->columns || result->rows != A->rows ||
        result->columns != A->columns)
        return CALC_ERROR;
    // get cofactor of a matrix |A|
    return OK;
}

double s21_determinant(matrix_t *A) {
    if (A->rows != A->columns)
        return CALC_ERROR;
    if (A->rows == 0)
        return A->matrix[0][0];

    return det(A->matrix, A->rows);
}

double det(double **m, int size) {
    double res = 0;
    if (size == 1)
        return m[0][0];

    double **tmp = malloc(sizeof(double *) * size);
    for (int i = 0; i < size; i++)
        tmp[i] = malloc(sizeof(double) * size);

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

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
    if (A->rows != A->columns)
        return CALC_ERROR;
    if (fabs(s21_determinant(A)) < 1e-6)
        return CALC_ERROR;

    matrix_t identity = {0};
    s21_create_matrix(A->rows, A->columns, &identity);
    set_to_identity(&identity);

    matrix_t joined = {0};
    s21_create_matrix(A->rows, A->columns * 2, &joined);

    int cur_row;
    int cur_col;
    int max_iterations = 100;
    bool complete = false;
    for (int i = 0; i < max_iterations && !complete; i++) {
        for (int diag_idx = 0; diag_idx < joined.rows; diag_idx++) {
            cur_row = diag_idx;
            cur_col = diag_idx;

            int max = find_row_with_max_elem(&joined, cur_col, cur_row);

            if (max != cur_row)
                swap_rows(&joined, cur_row, max);

            if (joined.matrix[cur_row][cur_col] != 1.0) {
                double mult_factor = 1.0 / joined.matrix[cur_row][cur_col];
                mult_row(&joined, cur_row, mult_factor);
            }

            for (int row_idx = cur_row + 1; row_idx < joined.rows; row_idx++) {
                if (fabs(joined.matrix[row_idx][cur_row]) > 1e-6) {
                    int row_one_idx = cur_col;

                    double cur_elem_value = joined.matrix[row_idx][cur_col];
                    double row_one_val = joined.matrix[row_one_idx][cur_col];

                    if (fabs(row_one_val) > 1e-6) {
                        double correction = -(cur_elem_value / row_one_val);
                        mult_add(&joined, row_idx, row_one_idx, correction);
                    }
                }
            }

            for (int col_idx = cur_col + 1; col_idx < joined.rows; col_idx++) {
                if (fabs(joined.matrix[cur_row][cur_col]) > 1e-6) {
                    int row_one_idx = col_idx;

                    double cur_elem_value = joined.matrix[cur_row][col_idx];
                    double row_one_val = joined.matrix[row_one_idx][col_idx];

                    if (fabs(row_one_val) > 1e-6) {
                        double correction = -(cur_elem_value / row_one_val);
                        mult_add(&joined, cur_row, row_one_idx, correction);
                    }
                }
            }

            if (check_matrix(&joined, &identity)) {
                copy_result(result, &joined);
                complete = true;
            }
        }
    }

    if (!complete)
        return CALC_ERROR;

    s21_remove_matrix(&joined);
    s21_remove_matrix(&identity);
    return OK;
}

void copy_result(matrix_t *res, matrix_t *m) {
    for (int i = 0; i < m->rows; i++)
        for (int j = m->rows; j < m->rows * 2; j++)
            res->matrix[i][j - m->rows] = m->matrix[i][j];
}
bool check_matrix(matrix_t *m, matrix_t *identity) {
    bool res = true;
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->rows; j++) {
            if (m->matrix[i][j] != identity->matrix[i][j]) {
                res = false;
                break;
            }
        }
    }
    return res;
}

void swap_rows(matrix_t *m, int row_a, int row_b) {
    for (int i = 0; i < m->columns; i++) {
        double tmp = m->matrix[row_a][i];
        m->matrix[row_a][i] = m->matrix[row_b][i];
        m->matrix[row_b][i] = tmp;
    }
}

void set_to_identity(matrix_t *m) {
    for (int i = 0; i < m->rows; i++)
        for (int j = 0; j < m->columns; j++)
            if (i == j)
                m->matrix[i][j] = 1.0;
            else
                m->matrix[i][j] = 0.0;
}

matrix_t join_matrices(matrix_t *a, matrix_t *b) {
    matrix_t res = {0};
    int rows = a->rows;
    int cols = a->columns + b->columns;
    s21_create_matrix(rows, cols, &res);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (j < a->columns)
                res.matrix[i][j] = a->matrix[i][j];
            else
                res.matrix[i][j] = b->matrix[i][j - a->columns];
        }
    }

    return res;
}

void mult_add(matrix_t *m, int i, int j, int mult_factor) {
    for (int k = 0; k < m->columns; k++)
        m->matrix[i][k] += m->matrix[j][k] * mult_factor;
}

void mult_row(matrix_t *m, int row, double mult_factor) {
    for (int i = 0; i < m->columns; i++)
        m->matrix[row][i] *= mult_factor;
}

int find_row_with_max_elem(matrix_t *m, int col, int start_row) {
    double max = m->matrix[start_row][col];
    int res = start_row;
    for (int i = start_row + 1; i < m->rows; i++) {
        if (fabs(m->matrix[i][col]) - fabs(max) > 1e-6) {
            res = i;
            max = m->matrix[i][col];
        }
    }

    return res;
}
