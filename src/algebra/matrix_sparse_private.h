#ifndef MATRIX_SPARSE_PRIVATE_H
#define MATRIX_SPARSE_PRIVATE_H

#include "matrix_sparse.h"
#include "cs.h"

/**************************** matrix_sparse_wrapper ***************************/
void matrix_sparse_to_cs(cs * a0, const matrix_sparse * a);
void matrix_sparse_from_cs(matrix_sparse * a, const cs * a0);

/**************************** matrix_sparse_fscan *****************************/
matrix_sparse * matrix_sparse_fscan_raw(FILE * in);

#define MATRIX_SPARSE_FSCAN_FORMAT_TOTAL 1

static const char *
matrix_sparse_fscan_format[MATRIX_SPARSE_FSCAN_FORMAT_TOTAL] =
{
  "--raw"
};

typedef matrix_sparse * (*matrix_sparse_fscan_function_type)(FILE *);

static const matrix_sparse_fscan_function_type
matrix_sparse_fscan_function[MATRIX_SPARSE_FSCAN_FORMAT_TOTAL] =
{
  matrix_sparse_fscan_raw
};

/**************************** matrix_sparse_fprint ****************************/
void matrix_sparse_fprint_only_values(FILE * out, const matrix_sparse * a);
void matrix_sparse_fprint_raw(FILE * out, const matrix_sparse * a);
void matrix_sparse_fprint_annotated(FILE * out, const matrix_sparse * a);
void matrix_sparse_fprint_matrix_form_raw(FILE * out, const matrix_sparse * a);
void matrix_sparse_fprint_matrix_form_curly(
  FILE * out, const matrix_sparse * a);
void matrix_sparse_fprint_mathematica_sparse(
  FILE * out, const matrix_sparse * a);

#define MATRIX_SPARSE_FPRINT_FORMAT_TOTAL 6

static const char *
matrix_sparse_fprint_format[MATRIX_SPARSE_FPRINT_FORMAT_TOTAL] =
{
  "--only-values",
  "--raw",
  "--annotated",
  "--matrix-form-raw",
  "--matrix-form-curly",
  "--mathematica-sparse"
};

typedef void (*matrix_sparse_fprint_function_type)(
  FILE *, const matrix_sparse *);

static const matrix_sparse_fprint_function_type
matrix_sparse_fprint_function[MATRIX_SPARSE_FPRINT_FORMAT_TOTAL] =
{
  matrix_sparse_fprint_only_values,
  matrix_sparse_fprint_raw,
  matrix_sparse_fprint_annotated,
  matrix_sparse_fprint_matrix_form_raw,
  matrix_sparse_fprint_matrix_form_curly,
  matrix_sparse_fprint_mathematica_sparse
};

/************************* matrix_sparse_linear_solve *************************/
void matrix_sparse_linear_solve_cholesky(const matrix_sparse * a, double * b);
void matrix_sparse_linear_solve_lu(const matrix_sparse * a, double * b);

#define MATRIX_SPARSE_LINEAR_SOLVE_METHOD_TOTAL 2

static const char *
matrix_sparse_linear_solve_method[MATRIX_SPARSE_LINEAR_SOLVE_METHOD_TOTAL] =
{
  "--cholesky",
  "--lu"
};

typedef void (*matrix_sparse_linear_solve_function_type)(
  const matrix_sparse * a, double * b);

static const matrix_sparse_linear_solve_function_type 
matrix_sparse_linear_solve_function[MATRIX_SPARSE_LINEAR_SOLVE_METHOD_TOTAL] =
{
  matrix_sparse_linear_solve_cholesky,
  matrix_sparse_linear_solve_lu
};

/*********************** matrix_sparse_laplace_equation ***********************/
void matrix_sparse_laplace_equation_rhs_vector_modify(
  double * b_in, const matrix_sparse * m_laplacian, const jagged1 * m_nodes_in,
  const jagged1 * m_nodes_bd, const double * b_bd);

#endif /* MATRIX_SPARSE_PRIVATE_H */
