#ifndef __MATRIX__

#include <stdlib.h>

void print_mat(float **C,
               const size_t C_f_row,
               const size_t C_f_col,
               const size_t n);

int naive_matrix_mult(float **C,
                        float **A,
                        float **B,
                        const size_t A_rows,
                        const size_t A_cols,
                        const size_t B_rows,
                        const size_t B_cols);

float **allocate_matrix(const size_t rows,
                        const size_t cols);

void deallocate_matrix(float **A, const size_t rows);

int same_matrix(float **A, const size_t A_rows, const size_t A_cols,
		float **B, const size_t B_rows, const size_t B_cols);

#endif // __MATRIX__
