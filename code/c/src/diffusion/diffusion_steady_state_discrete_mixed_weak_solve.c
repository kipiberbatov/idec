#include <errno.h>
#include <stdlib.h>

#include "diffusion_steady_state_discrete_mixed_weak.h"
#include "mesh_qc.h"

static void matrix_sparse_mixed_constrained_solve_with_diagonal_square_matrix(
  double * q,
  double * u,
  const double * a,
  const matrix_sparse * b,
  const double * g,
  const double * f,
  const jagged1 * boundary,
  const double * boundary_condition)
{
  return;
}

void diffusion_steady_state_discrete_mixed_weak_solve(
  double * q,
  double * u,
  const mesh * m,
  const matrix_sparse * m_bd_d,
  const double * m_inner_dm1,
  const diffusion_steady_state_discrete_mixed_weak * data)
{
  double * a;
  double * f, * g = NULL;
  matrix_sparse * b;

  a = (double *) malloc(sizeof(double) * m->cn[m->dim - 1]);
  if (a == NULL)
  {
    fprintf(stderr,
      "%s:%d: cannot allocate memory for a\n", __FILE__, __LINE__);
    return;
  }
  mesh_qc_matrix_diagonal_from_inner_of_basis_dm1_cup_inverse_pi_2_basis_dm1(
    a, m, m_inner_dm1, data->pi_dm1);

  b = mesh_qc_matrix_sparse_from_integral_of_basis_0_cup_delta_basis_dm1(
    m, m_bd_d);
  if (b == NULL)
  {
    fprintf(stderr, "%s:%d: cannot calculate b\n", __FILE__, __LINE__);
    goto a_free;
  }

  /* allocate memory for g */
  if (g == NULL)
  {
    fprintf(stderr,
      "%s:%d: cannot allocate memory for g\n", __FILE__, __LINE__);
    goto b_free;
  }
  mesh_qc_vector_from_boundary_integral_of_basis_dm1_cup_0_cochain(
    g, m, data->boundary_dirichlet, data->g_dirichlet);

  f = (double *) malloc(sizeof(double) * m->cn[0]);
  if (f == NULL)
  {
    fprintf(stderr,
      "%s:%d: cannot allocate memory for f\n", __FILE__, __LINE__);
    goto g_free;
  }
  mesh_qc_vector_from_integral_of_basis_0_cup_d_cochain(f, m, data->source);

  matrix_sparse_mixed_constrained_solve_with_diagonal_square_matrix(
    q, u, a, b, g, f, data->boundary_neumann, data->g_neumann);
  if (errno)
  {
    fprintf(stderr,
      "%s:%d: cannot solve linear system for q and u\n", __FILE__, __LINE__);
    goto f_free;
  }

f_free:
  free(f);
g_free:
  free(g);
b_free:
  matrix_sparse_free(b);
a_free:
  free(a);
}
