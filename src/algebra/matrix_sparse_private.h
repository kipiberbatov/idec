#ifndef _matrix_sparse_private_h
#define _matrix_sparse_private_h

#include "matrix_sparse.h"
#include "cs.h"

/**************************** matrix_sparse_wrapper ***************************/
void matrix_sparse_to_cs(cs * a0, const matrix_sparse * a);
void matrix_sparse_from_cs(matrix_sparse * a, const cs * a0);

/**************************** matrix_sparse_file_scan *****************************/
matrix_sparse * matrix_sparse_file_scan_raw(FILE * in);

/**************************** matrix_sparse_file_print ****************************/
void matrix_sparse_file_print_only_values(FILE * out, const matrix_sparse * a);
void matrix_sparse_file_print_raw(FILE * out, const matrix_sparse * a);
void matrix_sparse_file_print_annotated(FILE * out, const matrix_sparse * a);
void matrix_sparse_file_print_matrix_form_raw(FILE * out, const matrix_sparse * a);
void matrix_sparse_file_print_matrix_form_curly(
  FILE * out, const matrix_sparse * a);
void matrix_sparse_file_print_mathematica_sparse(
  FILE * out, const matrix_sparse * a);

/************************* matrix_sparse_linear_solve *************************/
void matrix_sparse_linear_solve_cholesky(const matrix_sparse * a, double * b);
void matrix_sparse_linear_solve_lu(const matrix_sparse * a, double * b);

/*********************** matrix_sparse_laplace_equation ***********************/
void matrix_sparse_laplace_equation_rhs_vector_modify(
  double * b_in, const matrix_sparse * m_laplacian, const jagged1 * m_nodes_in,
  const jagged1 * m_nodes_bd, const double * b_bd);

#endif /* _matrix_sparse_private_h */
