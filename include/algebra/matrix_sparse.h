#ifndef MATRIX_SPARSE_H
#define MATRIX_SPARSE_H

#include <stdio.h>
#include "jagged.h"

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

void matrix_sparse_free_shared(matrix_sparse * a);

/**************************** matrix_sparse_fscan *****************************/
/* Supported formats for "matrix_sparse_fscan":
 * --raw
 */

matrix_sparse * matrix_sparse_fscan(FILE * in, const char * format);

matrix_sparse * matrix_sparse_fscan_by_name(
  const char * name, const char * format);


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

/********************* matrix_sparse algebraic operations *********************/
matrix_sparse * matrix_sparse_identity(int n);

matrix_sparse * matrix_sparse_linear_combination(
  const matrix_sparse * a, const matrix_sparse * b, double alpha, double beta);

matrix_sparse * matrix_sparse_add(
  const matrix_sparse * a, const matrix_sparse * b);

matrix_sparse * matrix_sparse_product(
  const matrix_sparse * a, const matrix_sparse * b);

matrix_sparse * matrix_sparse_transpose(const matrix_sparse * a);

matrix_sparse * matrix_sparse_laplacian_0(const matrix_sparse * a_0, const matrix_sparse * b_1);

matrix_sparse * matrix_sparse_laplacian_p(
  const matrix_sparse * a_p_minus_1, const matrix_sparse * a_p, 
  const matrix_sparse * b_p, const matrix_sparse * b_p_plus_1);

matrix_sparse * matrix_sparse_laplacian_d(
  const matrix_sparse * a_d_minus_1, const matrix_sparse * b_d);

matrix_sparse ** matrix_sparse_laplacian(
  int d, matrix_sparse ** a, matrix_sparse ** b);

void matrix_sparse_laplacian_fprint(
  FILE * out, int d, matrix_sparse ** a, matrix_sparse ** b,
  const char * format);

void matrix_sparse_laplacian_symmetric(
  matrix_sparse ** delta, int d, double ** m_inner);

double * matrix_sparse_diffusion(
  const matrix_sparse * laplacian_0, const double * lhs, const double * u_0,
  double tau, int N);

typedef double (*scalar_field)(const double *);

double * matrix_sparse_laplace_equation_solve(
  const matrix_sparse * m_laplacian, int m_dim_embedded, const double * m_coord,
  const jagged1 * m_nodes_bd, scalar_field f, scalar_field g_d);

double * matrix_sparse_laplace_equation_solve_non_grid(
  const matrix_sparse * m_laplacian, int m_dim_embedded, const double * m_coord,
  const double * m_inner, const jagged1 * m_nodes_bd, scalar_field f,
  scalar_field g_d);

/************************* matrix_sparse_linear_solve *************************/
/* Supported methods for "matrix_sparse_linear_solve":
 * --cholesky
 */

void matrix_sparse_linear_solve(
  const matrix_sparse * a, double * b, const char * method);

/**************************** matrix_sparse_remove ****************************/
matrix_sparse * matrix_sparse_restrict(
  const matrix_sparse * a, const jagged1 * rows_complement,
  const jagged1 * cols_complement);

matrix_sparse * matrix_sparse_restrict_symmetric(
  const matrix_sparse * a, const jagged1 * rows_complement);

matrix_sparse * matrix_sparse_remove(
  const matrix_sparse * a, const jagged1 * rows, const jagged1 * cols);

matrix_sparse * matrix_sparse_remove_symmetric(
  const matrix_sparse * a, const jagged1 * rows);

double * matrix_sparse_constrained_solve_cholesky(
  const matrix_sparse * a, const double * b, const jagged1 * rows);

/***************************** matrix_sparse_array ****************************/
matrix_sparse ** matrix_sparse_array_fscan(
  FILE * in, int n, const char * format);

matrix_sparse ** matrix_sparse_array_fscan_by_name(
  const char * name, int n, const char * format);

void matrix_sparse_array_fprint(
  FILE * out, int n, matrix_sparse ** a, const char * format);

void matrix_sparse_array_free(matrix_sparse ** a, int n);

void matrix_sparse_array_free_shared(matrix_sparse ** a, int n);

#endif /* MATRIX_SPARSE_H */
