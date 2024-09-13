#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "mesh_qc.h"
#include "diffusion_steady_state_discrete_primal_weak.h"

static void double_array_add_sparse_to(
  double * f, const jagged1 * indices, const double * g)
{
  int i, i_local, indices_a0;
  int * indices_a1;

  indices_a0 = indices->a0;
  indices_a1 = indices->a1;
  for (i_local = 0; i_local < indices_a0; ++i_local)
  {
    i = indices_a1[i_local];
    f[i] += g[i_local];
  }
}

static double * matrix_sparse_symmetric_constrained_solve(
  matrix_sparse * a,
  double * f,
  const jagged1 * rows,
  const double * values)
{
  int i, i_local, rows_a0;
  int * rows_a1;
  double * u;

  rows_a0 = rows->a0;
  rows_a1 = rows->a1;
  matrix_sparse_set_identity_rows(a, rows);
  for (i_local = 0; i_local < rows_a0; ++i_local)
  {
    i = rows_a1[i_local];
    f[i] = values[i_local];
  }
  u = (double *) malloc(sizeof(double) * a->cols);
  if (u == NULL)
    return NULL;
  memcpy(u, f, sizeof(double) * a->cols);
  matrix_sparse_linear_solve(a, u, "--lu");
  if (errno)
    return NULL;
  return u;
}

double * diffusion_steady_state_discrete_primal_weak_solve(
  const mesh * m,
  const double * m_inner_1,
  const diffusion_steady_state_discrete_primal_weak * data)
{
  int m_cn_0;
  double * f, * g, * u = NULL;
  matrix_sparse * a;

  m_cn_0 = m->cn[0];

  a = mesh_qc_matrix_sparse_from_inner_of_delta_basis_0_cup_pi_1_delta_basis_0(
    m, m_inner_1, data->pi_1);
  if (a == NULL)
    goto end;

  f = (double *) malloc(sizeof(double) * m_cn_0);
  if (f == NULL)
    goto a_free;
  mesh_qc_vector_from_integral_of_basis_0_cup_d_cochain(f, m, data->source);

  g = (double *) malloc(sizeof(double) * data->boundary_neumann->a0);
  if (f == NULL)
    goto f_free;
  mesh_qc_vector_from_boundary_integral_of_basis_0_cup_dm1_cochain(
    g, m, data->boundary_neumann, data->g_neumann);

  double_array_add_sparse_to(f, data->boundary_neumann, g);

  u = matrix_sparse_symmetric_constrained_solve(
    a, f, data->boundary_dirichlet, data->g_dirichlet);

  free(g);
f_free:
  free(f);
a_free:
  matrix_sparse_free(a);
end:
  return u;
}
