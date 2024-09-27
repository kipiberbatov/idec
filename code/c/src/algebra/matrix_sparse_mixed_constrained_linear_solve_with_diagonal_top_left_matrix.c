#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"
#include "double.h"
#include "matrix_sparse.h"

static void set_f_new(
  double * f_new,
  const double * f,
  const matrix_sparse * b,
  const jagged1 * boundary_neumann,
  const double * g_neumann)
{
  int boundary_neumann_a0, i, i_local, k, k_local;
  int * b_cols_total, * b_row_indices, * boundary_neumann_a1;
  double lambda_i;
  double * b_values;

  boundary_neumann_a0 = boundary_neumann->a0;
  boundary_neumann_a1 = boundary_neumann->a1;
  b_cols_total = b->cols_total;
  b_row_indices = b->row_indices;
  b_values = b->values;

  memcpy(f_new, f, sizeof(double) * b->rows);
  for (i_local = 0; i_local < boundary_neumann_a0; ++i_local)
  {
    i = boundary_neumann_a1[i_local];
    lambda_i = g_neumann[i_local];
    for (k_local = b_cols_total[i]; k_local < b_cols_total[i + 1]; ++k_local)
    {
      k = b_row_indices[k_local];
      f_new[k] -= b_values[k_local] * lambda_i;
    }
  }
}

static void set_g_new(
  double * g_new,
  const double * a,
  const jagged1 * boundary_neumann,
  const double * g_neumann)
{
  int boundary_neumann_a0, i, i_local;
  int * boundary_neumann_a1;

  boundary_neumann_a0 = boundary_neumann->a0;
  boundary_neumann_a1 = boundary_neumann->a1;

  for (i_local = 0; i_local < boundary_neumann_a0; ++i_local)
  {
    i = boundary_neumann_a1[i_local];
    g_new[i] -= a[i] * g_neumann[i_local];
  }
}

void matrix_sparse_mixed_constrained_linear_solve_with_diagonal_top_left_matrix(
  double * flux,
  double * temperature,
  const double * a,
  const matrix_sparse * b,
  const double * g,
  const double * f,
  const jagged1 * boundary_neumann,
  const double * g_neumann)
{
  int restrict_size;
  double * a_restrict, * flux_restrict, * f_new, * g_new, * g_new_restrict;
  jagged1 * boundary_neumann_complement;
  matrix_sparse * b_restrict;

  boundary_neumann_complement = jagged1_complement(b->cols, boundary_neumann);
  if (boundary_neumann_complement == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate boundary_neumann_complement\n", stderr);
    return;
  }
  restrict_size = boundary_neumann_complement->a0;
  fprintf(stderr,
    "\n%sboundary_neumann_complement:%s\n", color_red, color_none);
  jagged1_file_print(stderr, boundary_neumann_complement, "--curly");

  a_restrict = (double *) malloc(sizeof(double) * restrict_size);
  if (a == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot allocate memory for a_restrict\n", stderr);
    goto boundary_neumann_complement_free;
  }
  double_array_substitute(a_restrict,
    restrict_size, a, boundary_neumann_complement->a1);
  fprintf(stderr, "\n%sa_restrict (diagonal):%s\n", color_red, color_none);
  double_array_file_print(stderr, restrict_size, a_restrict, "--curly");
  fputc('\n', stderr);

  b_restrict = matrix_sparse_columns_restrict(b, boundary_neumann_complement);
  if (b_restrict == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot allocate memory for b_restrict\n", stderr);
    goto a_restrict_free;
  }
  fprintf(stderr, "\n%sb_restrict:%s\n", color_red, color_none);
  matrix_sparse_file_print(stderr, b_restrict, "--matrix-form-curly");

  g_new = (double *) malloc(sizeof(double) * b->cols);
  if (g_new == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot allocate memory for g_new\n", stderr);
    goto b_restrict_free;
  }
  memcpy(g_new, g, sizeof(double) * b->cols);
  set_g_new(g_new, a, boundary_neumann, g_neumann);
  fprintf(stderr, "\n%sg_new:%s\n", color_red, color_none);
  double_array_file_print(stderr, b->cols, g_new, "--curly");
  fputc('\n', stderr);

  g_new_restrict = (double *) malloc(sizeof(double) * restrict_size);
  if (g_new_restrict == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot allocate memory for g_new_restrict\n", stderr);
    goto g_new_free;
  }
  double_array_substitute(g_new_restrict,
    restrict_size, g_new, boundary_neumann_complement->a1);
  fprintf(stderr, "\n%sg_new_restrict:%s\n", color_red, color_none);
  double_array_file_print(stderr, restrict_size, g_new_restrict, "--curly");
  fputc('\n', stderr);

  f_new = (double *) malloc(sizeof(double) * b->rows);
  if (f_new == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot allocate memory for f_new\n", stderr);
    goto g_new_restrict_free;
  }
  set_f_new(f_new, f, b, boundary_neumann, g_neumann);
  fprintf(stderr, "\n%sf_new:%s\n", color_red, color_none);
  double_array_file_print(stderr, b->rows, f_new, "--curly");
  fputc('\n', stderr);

  flux_restrict = (double *) malloc(sizeof(double) * restrict_size);
  if (flux_restrict == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot allocate memory for flux_restrict\n", stderr);
    goto f_new_free;
  }

  matrix_sparse_mixed_linear_solve_with_diagonal_top_left_matrix(
    flux_restrict, temperature, a_restrict, b_restrict, g_new_restrict, f_new);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot solve restricted mixed linear system\n", stderr);
    goto flux_restrict_free;
  }

  double_array_substitute_inverse(flux,
    restrict_size, flux_restrict, boundary_neumann_complement->a1);
  double_array_substitute_inverse(flux,
    boundary_neumann->a0, g_neumann, boundary_neumann->a1);

flux_restrict_free:
  free(flux_restrict);
f_new_free:
  free(f_new);
g_new_restrict_free:
  free(g_new_restrict);
g_new_free:
  free(g_new);
b_restrict_free:
  matrix_sparse_free(b_restrict);
a_restrict_free:
  free(a_restrict);
boundary_neumann_complement_free:
  jagged1_free(boundary_neumann_complement);
}
