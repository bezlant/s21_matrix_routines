#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 4096

enum { OK = 0, INCORRECT_MATRIX = 1, CALC_ERROR = 2, MALLOC_FAILED = 3 };
enum { FAILURE = 0, SUCCESS = 1 };

typedef struct matrix_struct {
    double **matrix;
    int rows;
    int columns;
} matrix_t;
// maybe need to malloc result
int s21_create_matrix(const int rows, const int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *const A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
// TODO
double s21_determinant(matrix_t *A);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

// helpers
void swap_rows(matrix_t *m, int row_a, int row_b);
void set_to_identity(matrix_t *m);
matrix_t join_matrices(matrix_t *a, matrix_t *b);
void mult_add(matrix_t *m, int i, int j, int mult_factor);
void mult_row(matrix_t *m, int row, double mult_factor);
int find_row_with_max_elem(matrix_t *m, int col, int start_row);
bool check_matrix(matrix_t *m, matrix_t *identity);
void copy_result(matrix_t *res, matrix_t *m);
#endif  // SRC_S21_MATRIX_H
