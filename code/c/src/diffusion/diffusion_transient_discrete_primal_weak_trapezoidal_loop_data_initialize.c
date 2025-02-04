#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"
#include "diffusion_discrete_set_neumann_rows.h"
#include "diffusion_transient_discrete_primal_weak.h"
#include "diffusion_transient_discrete_primal_weak_trapezoidal_loop_data.h"
#include "double.h"
#include "idec_error_message.h"
#include "mesh_qc.h"

struct diffusion_transient_discrete_primal_weak_trapezoidal_loop_data *
diffusion_transient_discrete_primal_weak_trapezoidal_loop_data_initialize(
  const struct mesh * m,
  const double * m_inner_0,
  const double * m_inner_1,
  const struct diffusion_transient_discrete_primal_weak * data,
  double time_step)
{
  int m_cn_0;
  double * b, * f, * free_part, * g;
  struct matrix_sparse * a, * lhs, * rhs;
  struct diffusion_transient_discrete_primal_weak_trapezoidal_loop_data *
    result;

  *(void **) (&result) = malloc(sizeof(*result));
  if (result == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    idec_error_message_malloc(sizeof(*result), "result");
    goto end;
  }

  m_cn_0 = m->cn[0];

  a =
  mesh_qc_matrix_sparse_from_inner_of_delta_basis_0_cup_kappa_1_delta_basis_0(
    m, m_inner_1, data->kappa_1);
  if (a == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate matrix a\n", stderr);
    goto result_free;
  }

  b = (double *) malloc(sizeof(double) * m_cn_0);
  if (b == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    idec_error_message_malloc(sizeof(double) * m_cn_0, "b");
    goto a_free;
  }
  mesh_qc_matrix_diagonal_from_inner_of_basis_0_cup_pi_0_basis_0(
    b, m, m_inner_0, data->pi_0);

  lhs = a;
  rhs = matrix_sparse_copy(a);
  if (rhs == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "%s:%d: cannot copy sparse matrix a\n", __FILE__, __LINE__);
    goto b_free;
  }

  /* $lhs = (time_step / 2) * a + b$ */
  matrix_sparse_scalar_multiply(lhs, time_step / 2);
  matrix_sparse_add_with_diagonal_matrix(lhs, b);

  /* $rhs = - (time_step / 2) * a + b$ */
  matrix_sparse_scalar_multiply(rhs, - time_step / 2);
  matrix_sparse_add_with_diagonal_matrix(rhs, b);
  free(b);
  b = NULL;

  f = (double *) malloc(sizeof(double) * m_cn_0);
  if (f == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    idec_error_message_malloc(sizeof(double) * m_cn_0, "f");
    goto rhs_free;
  }
  mesh_qc_vector_from_integral_of_basis_0_cup_d_cochain(f, m, data->source);

  g = (double *) malloc(sizeof(double) * data->boundary_neumann->a0);
  if (g == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    idec_error_message_malloc(sizeof(double) * data->boundary_neumann->a0, "g");
    goto f_free;
  }
  mesh_qc_vector_from_boundary_integral_of_basis_0_cup_dm1_cochain(
    g, m, data->boundary_neumann, data->g_neumann);

  double_array_add_sparse_to(f, data->boundary_neumann, g);
  free(g);

  /* $free_part = time_step * rhs_vector$ */
  free_part = f;
  double_array_multiply_with(free_part, m_cn_0, time_step);

  /* apply Dirichlet boundary condition on matrix $lhs$ */
  matrix_sparse_set_identity_rows(lhs, data->boundary_dirichlet);

  result->lhs = lhs;
  result->rhs = rhs;
  result->free_part = free_part;
  result->data = data;
  return result;

  /* cleaning if an error occurs */
f_free:
  free(f);
rhs_free:
  matrix_sparse_free(rhs);
b_free:
  free(b);
a_free:
  matrix_sparse_free(a);
result_free:
  free(result);
end:
  return NULL;
}
