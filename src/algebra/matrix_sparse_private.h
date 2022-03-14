#ifndef MATRIX_SPARSE_PRIVATE_H
#define MATRIX_SPARSE_PRIVATE_H

#include "matrix_sparse.h"
#include "cs.h"

/**************************** matrix_sparse_wrapper ***************************/
void matrix_sparse_to_cs(cs * a0, const matrix_sparse * a);
void matrix_sparse_from_cs(matrix_sparse * a, const cs * a0);

/**************************** matrix_sparse_fscan *****************************/
matrix_sparse * matrix_sparse_fscan_raw(FILE * in);

#define FSCAN_FORMATS_TOTAL 1

static const char * fscan_formats[FSCAN_FORMATS_TOTAL] =
  {
    "--raw"
  };

typedef matrix_sparse * (*matrix_sparse_fscan_func)(FILE *);
static const matrix_sparse_fscan_func fscanners[FSCAN_FORMATS_TOTAL] =
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

#define FPRINT_FORMATS_TOTAL 6

static const char * fprint_formats[FPRINT_FORMATS_TOTAL] =
  {
    "--only-values",
    "--raw",
    "--annotated",
    "--matrix-form-raw",
    "--matrix-form-curly",
    "--mathematica-sparse"
  };

typedef void (*matrix_sparse_fprint_func)(FILE *, const matrix_sparse *);
static const matrix_sparse_fprint_func fprinters[FPRINT_FORMATS_TOTAL] =
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

#define LINEAR_SOLVE_METHODS_TOTAL 1

static const char * linear_solve_methods[LINEAR_SOLVE_METHODS_TOTAL] =
  {
    "--cholesky"
  };

typedef void (*matrix_sparse_linear_solve_func)(
  const matrix_sparse * a, double * b);

static const matrix_sparse_linear_solve_func 
linear_solvers[LINEAR_SOLVE_METHODS_TOTAL] =
  {
    matrix_sparse_linear_solve_cholesky
  };

#endif /* MATRIX_SPARSE_PRIVATE_H */
