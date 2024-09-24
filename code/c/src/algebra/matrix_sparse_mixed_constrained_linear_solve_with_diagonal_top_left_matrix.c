#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "double.h"
#include "matrix_sparse.h"

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
  int i, i_local, k, k_local, restrict_size;
  double lambda_i;
  double * a_restrict, * flux_restrict, * f_new, * g_new, * g_new_restrict;
  jagged1 * boundary_neumann_complement;
  matrix_sparse * b_restrict;

  boundary_neumann_complement = jagged1_complement(b->cols, boundary_neumann);
  if (boundary_neumann_complement == NULL)
  {
    fprintf(stderr,
      "%s:%d: cannot allocate memory for a\n", __FILE__, __LINE__);
    return;
  }
  restrict_size = boundary_neumann_complement->a0;

  a_restrict = (double *) malloc(sizeof(double) * restrict_size);
  if (a == NULL)
  {
    fprintf(stderr,
      "%s:%d: cannot allocate memory for a\n", __FILE__, __LINE__);
    goto boundary_neumann_complement_free;
  }
  double_array_substitute(a_restrict,
    restrict_size, a, boundary_neumann_complement->a1);

  b_restrict = matrix_sparse_columns_restrict(b, boundary_neumann_complement);
  if (b_restrict == NULL)
  {
    fprintf(stderr,
      "%s:%d: cannot allocate memory for b_restrict\n", __FILE__, __LINE__);
    goto a_restrict_free;
  }

  g_new = malloc(sizeof(double) * b->cols);
  if (g_new == NULL)
  {
    fprintf(stderr,
      "%s:%d: cannot allocate memory for g_new\n", __FILE__, __LINE__);
    goto b_restrict_free;
  }
  for (i_local = 0; i_local < boundary_neumann->a0; ++i_local)
  {
    i = boundary_neumann->a1[i_local];
    g_new[i] -= a[i] * g_neumann[i_local];
  }

  g_new_restrict = malloc(sizeof(double) * restrict_size);
  if (g_new_restrict == NULL)
  {
    fprintf(stderr,
      "%s:%d: cannot allocate memory for g_new_restrict\n", __FILE__, __LINE__);
    goto g_new_free;
  }
  double_array_substitute(g_new_restrict,
    restrict_size, g_new, boundary_neumann_complement->a1);

  f_new = malloc(sizeof(double) * b->rows);
  if (f_new == NULL)
  {
    fprintf(stderr,
      "%s:%d: cannot allocate memory for f_new\n", __FILE__, __LINE__);
    goto g_new_restrict_free;
  }
  memcpy(f_new, f, sizeof(double) * b->rows);
  for (i_local = 0; i_local < boundary_neumann->a0; ++i_local)
  {
    i = boundary_neumann->a1[i_local];
    lambda_i = g_neumann[i_local];
    for (k_local = b->cols_total[i]; k_local < b->cols_total[i + 1]; ++k_local)
    {
      k = b->row_indices[k_local];
      f_new[k] -= b->values[k_local] * lambda_i;
    }
  }

  flux_restrict = (double *) malloc(sizeof(double) * restrict_size);
  if (flux_restrict == NULL)
  {
    fprintf(stderr,
      "%s:%d: cannot allocate memory for flux_restrict\n", __FILE__, __LINE__);
    goto f_new_free;
  }
  matrix_sparse_mixed_linear_solve_with_diagonal_top_left_matrix(
    flux_restrict, temperature, a_restrict, b_restrict, g_new_restrict, f_new);
  if (errno)
  {
    fprintf(stderr,
      "%s:%d: cannot solve restricted mixed linear system\n",
      __FILE__, __LINE__);
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
