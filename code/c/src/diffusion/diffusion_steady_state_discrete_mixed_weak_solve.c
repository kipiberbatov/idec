#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"
#include "diffusion_steady_state_discrete_mixed_weak.h"
#include "double.h"
#include "mesh_qc.h"

void diffusion_steady_state_discrete_mixed_weak_solve(
  double * flux,
  double * temperature,
  const mesh * m,
  const matrix_sparse * m_bd_d,
  const double * m_inner_dm1,
  const double * m_inner_d,
  const diffusion_steady_state_discrete_mixed_weak * data)
{
  int d;
  double * a;
  double * f, * g, * g_small;
  matrix_sparse * b;

  d = m->dim;

  a = (double *) malloc(sizeof(double) * m->cn[d - 1]);
  if (a == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot allocate memory for a\n", stderr);
    return;
  }
  mesh_qc_matrix_diagonal_from_inner_of_basis_dm1_cup_inverse_pi_2_basis_dm1(
    a, m, m_inner_dm1, data->pi_dm1);
  fprintf(stderr, "\n%sa_original:%s\n", color_red, color_none);
  double_array_file_print(stderr, m->cn[d - 1], a, "--curly");

  // b = mesh_qc_matrix_sparse_from_integral_of_basis_0_cup_delta_basis_dm1(
  //   m, m_cbd_dm1);
  b = mesh_qc_matrix_sparse_from_inner_of_basis_d_cup_delta_basis_dm1(
    m, m_bd_d, m_inner_d);
  if (b == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate b\n", stderr);
    goto a_free;
  }
  fprintf(stderr, "\n%sb_original:%s\n", color_red, color_none);
  matrix_sparse_file_print(stdout, b, "--matrix-form-curly");

  g_small = (double *) malloc(sizeof(double) * data->boundary_dirichlet->a0);
  if (g_small == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot allocate memory for g_small\n", stderr);
    goto b_free;
  }
  mesh_qc_vector_from_boundary_integral_of_basis_dm1_cup_0_cochain(
    g_small, m, data->boundary_dirichlet, data->g_dirichlet);
  fprintf(stderr, "\n%sg_small:%s\n", color_red, color_none);
  double_array_file_print(stderr,
    data->boundary_dirichlet->a0, g_small, "--curly");

  g = (double *) malloc(sizeof(double) * m->cn[d - 1]);
  if (g == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot allocate memory for g\n", stderr);
    goto g_small_free;
  }
  double_array_substitute_inverse(
    g, data->boundary_dirichlet->a0, g_small, data->boundary_dirichlet->a1);
  fprintf(stderr, "\n%sg:%s\n", color_red, color_none);
  double_array_file_print(stderr, m->cn[d - 1], g, "--curly");

  f = (double *) malloc(sizeof(double) * m->cn[d]);
  if (f == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot allocate memory for f\n", stderr);
    goto g_free;
  }
  mesh_qc_vector_from_inner_of_basis_d_cup_d_cochain(
    f, m, m_inner_d, data->source);
  fprintf(stderr, "\n%sf:%s\n", color_red, color_none);
  double_array_file_print(stderr, m->cn[d], f, "--curly");
  // mesh_qc_vector_from_integral_of_basis_0_cup_d_cochain(f, m, data->source);

  matrix_sparse_mixed_constrained_linear_solve_with_diagonal_top_left_matrix(
    flux, temperature, a, b, g, f, data->boundary_neumann, data->g_neumann);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot find flux and temperature\n", stderr);
    goto f_free;
  }

f_free:
  free(f);
g_free:
  free(g);
g_small_free:
  free(g_small);
b_free:
  matrix_sparse_free(b);
a_free:
  free(a);
}
