#ifndef MATRIX_SPARSE_H
#define MATRIX_SPARSE_H

#include <stdio.h>

typedef struct matrix_sparse
{
  int rows;
  int cols;
  int * cols_total;
  int * row_indices;
  double * values;
} matrix_sparse;

double matrix_sparse_part(const matrix_sparse * a, int i, int j);

/***************************** matrix_sparse_free *****************************/
void matrix_sparse_free(matrix_sparse * a);
void matrix_sparse_free_array(matrix_sparse ** a, int n);
void matrix_sparse_free_shared(matrix_sparse * a);
void matrix_sparse_free_shared_array(matrix_sparse ** a, int n);

/**************************** matrix_sparse_fscan *****************************/
/* Supported formats for "matrix_sparse_fscan":
 * --raw
 */

matrix_sparse * matrix_sparse_fscan(FILE * in, const char * format);
matrix_sparse ** matrix_sparse_fscan_array(
  FILE * in, int n, const char * format);

matrix_sparse * matrix_sparse_fscan_by_name(
  const char * name, const char * format);
matrix_sparse ** matrix_sparse_fscan_by_name_array(
  const char * name, int n, const char * format);

/**************************** matrix_sparse_fprint ****************************/
/* Supported formats for "matrix_sparse_fprint":
 * --only-values
 * --raw
 * --annotated
 * --matrix-form-raw
 * --matrix-form-curly
 * --mathematica-sparse
 */

void matrix_sparse_fprint(
  FILE * out, const matrix_sparse * a, const char * format);
void matrix_sparse_fprint_array(
  FILE * out, int n, matrix_sparse const * const * a, const char * format);

/********************* matrix_sparse algebraic operations *********************/
matrix_sparse * matrix_sparse_linear_combination(
  const matrix_sparse * a, const matrix_sparse * b, double alpha, double beta);

matrix_sparse * matrix_sparse_add(
  const matrix_sparse * a, const matrix_sparse * b);

matrix_sparse * matrix_sparse_product(
  const matrix_sparse * a, const matrix_sparse * b);

matrix_sparse * matrix_sparse_transpose(const matrix_sparse * a);

/************************* matrix_sparse_linear_solve *************************/
/* Supported methods for "matrix_sparse_linear_solve":
 * --cholesky
 */

void matrix_sparse_linear_solve(
  const matrix_sparse * a, double * b, const char * method);

#endif /* MATRIX_SPARSE_H */
