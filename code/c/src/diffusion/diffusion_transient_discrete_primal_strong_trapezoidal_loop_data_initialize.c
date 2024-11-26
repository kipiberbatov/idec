#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"
#include "diffusion_discrete_set_neumann_rows.h"
#include "diffusion_transient_discrete_primal_strong_trapezoidal_loop_data.h"

diffusion_transient_discrete_primal_strong_trapezoidal_loop_data *
diffusion_transient_discrete_primal_strong_trapezoidal_loop_data_initialize(
  const mesh * m,
  const matrix_sparse * m_cbd_0,
  const matrix_sparse * m_cbd_star_1,
  const diffusion_transient_discrete_primal_strong * data,
  double time_step)
{
  int n;
  double * a, * free_part;
  matrix_sparse * b, * lhs, * rhs;
  diffusion_transient_discrete_primal_strong_trapezoidal_loop_data * result;

  result = (diffusion_transient_discrete_primal_strong_trapezoidal_loop_data *)
    malloc(sizeof(
      diffusion_transient_discrete_primal_strong_trapezoidal_loop_data));
  if (result == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %ld bytes of memory for result\n",
      sizeof(diffusion_transient_discrete_primal_strong_trapezoidal_loop_data));
    goto end;
  }

  n = m->cn[0];
  a = data->pi_0;

  b = matrix_sparse_material_product(m_cbd_0, data->kappa_1, m_cbd_star_1);
  if (b == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate matrix b\n", stderr);
    goto result_free;
  }

  /* $lhs = a + (time_step / 2) * b$ */
  lhs = matrix_sparse_copy(b);
  if (lhs == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot initialize matrix lhs\n", stderr);
    goto b_free;
  }
  matrix_sparse_scalar_multiply(lhs, time_step / 2);
  matrix_sparse_add_with_diagonal_matrix(lhs, a);

  /* $rhs = a - (time_step / 2) * b$ */
  rhs = b;
  matrix_sparse_scalar_multiply(rhs, - time_step / 2);
  matrix_sparse_add_with_diagonal_matrix(rhs, a);

  /* $free_part = time_step * data->source$ */
  free_part = (double *) malloc(sizeof(double) * n);
  if (free_part == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %ld bytes of memory for free_part\n",
      sizeof(double) * n);
    goto lhs_free;
  }
  memcpy(free_part, data->source, sizeof(double) * n);
  double_array_multiply_with(free_part, n, time_step);

  /* apply Dirichlet boundary condition on matrix $lhs$ */
  matrix_sparse_set_identity_rows(lhs, data->boundary_dirichlet);

  /* apply Neumann boundary condition on matrix $lhs$ */
  diffusion_discrete_set_neumann_rows(
    lhs, m, data->boundary_neumann, data->kappa_1);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot apply Neumann boundary condition\n", stderr);
    goto free_part_free;
  }
  result->lhs = lhs;
  result->rhs = rhs;
  result->free_part = free_part;
  result->data = data;
  return result;

  /* cleaning if an error occurs */
free_part_free:
  free(free_part);
lhs_free:
  matrix_sparse_free(lhs);
b_free:
  matrix_sparse_free(b);
result_free:
  free(result);
end:
  return NULL;
}
