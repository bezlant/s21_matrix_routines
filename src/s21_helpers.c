#include "s21_matrix.h"

int is_correct(matrix_t *A) {
    return A && A->rows > 0 && A->columns > 0;
}
