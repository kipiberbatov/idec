#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"
#include "diffusion_steady_state_discrete_mixed_weak.h"
#include "double.h"
#include "mesh_qc.h"

#define progress 0

void diffusion_steady_state_discrete_mixed_weak_solve(
  double * flux,
  double * temperature_on_cells,
  const mesh * m,
  const matrix_sparse * m_cbd_dm1,
  const double * m_inner_dm1,
  const double * m_inner_d,
  const diffusion_steady_state_discrete_mixed_weak * data)
{
  int d;
  double * a;
  double * f, * g, * g_dirichlet_0_big;
  matrix_sparse * b;

  d = m->dim;

#if progress
  fprintf(stderr, "\n%sm_inner_%d:%s\n", color_red, d - 1, color_none);
  double_array_file_print(stderr, m->cn[d - 1], m_inner_dm1, "--curly");
  fputc('\n', stderr);
#endif

#if progress
  fprintf(stderr, "\n%spi_%d:%s\n", color_red, d - 1, color_none);
  double_array_file_print(stderr, m->cn[d - 1], data->pi_dm1, "--curly");
  fputc('\n', stderr);
#endif

  a = (double *) malloc(sizeof(double) * m->cn[d - 1]);
  if (a == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot allocate memory for a\n", stderr);
    return;
  }
  mesh_qc_matrix_diagonal_from_inner_of_basis_dm1_cup_inverse_pi_2_basis_dm1(
    a, m, m_inner_dm1, data->pi_dm1);

#if progress
  fprintf(stderr, "\n%sa_original:%s\n", color_red, color_none);
  double_array_file_print(stderr, m->cn[d - 1], a, "--curly");
  fputc('\n', stderr);
#endif

#if progress
  fprintf(stderr, "\n%sm_inner_%d:%s\n", color_red, d, color_none);
  double_array_file_print(stderr, m->cn[d], m_inner_d, "--curly");
  fputc('\n', stderr);
#endif

  b = mesh_qc_matrix_sparse_from_inner_of_basis_d_cup_delta_basis_dm1(
    m_cbd_dm1, m_inner_d);
  if (b == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate b\n", stderr);
    goto a_free;
  }
#if progress
  fprintf(stderr, "\n%sb_original:%s\n", color_red, color_none);
  matrix_sparse_file_print(stderr, b, "--matrix-form-curly");
#endif

  g_dirichlet_0_big = (double *) calloc(m->cn[0], sizeof(double));
  if (g_dirichlet_0_big == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot allocate memory for g_dirichlet_0_big\n", stderr);
    goto b_free;
  }
  double_array_assemble_from_sparse_array(
    g_dirichlet_0_big, data->boundary_dirichlet_0, data->g_dirichlet_0);

#if progress
  fprintf(stderr, "\n%sg_dirichlet_0_big:%s\n", color_red, color_none);
  double_array_file_print(stderr, m->cn[0], g_dirichlet_0_big, "--curly");
  fputc('\n', stderr);
#endif

  g = (double *) calloc(m->cn[d - 1], sizeof(double));
  if (g == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot allocate memory for g\n", stderr);
    goto g_dirichlet_0_big_free;
  }
  mesh_qc_vector_from_boundary_integral_of_basis_dm1_cup_0_cochain(
    g, m, m_cbd_dm1, data->boundary_dirichlet_dm1, g_dirichlet_0_big);

#if progress
  fprintf(stderr,
    "\n%sg = {(g_d \\_/ c^{%d, i})}_{i = 0}^{%d}:%s\n",
    color_red, d - 1, m->cn[d - 1] - 1, color_none);
  double_array_file_print(stderr, m->cn[d - 1], g, "--curly");
  fputc('\n', stderr);

#endif
  f = (double *) malloc(sizeof(double) * m->cn[d]);
  if (f == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot allocate memory for f\n", stderr);
    goto g_free;
  }
  mesh_qc_vector_from_inner_of_basis_d_cup_d_cochain(
    f, m, m_inner_d, data->source_d);
  double_array_multiply_with(f, m->cn[d], -1.);

#if progress
  fprintf(stderr, "\n%sf^%d:%s\n", color_red, d, color_none);
  double_array_file_print(stderr, m->cn[d], f, "--curly");
  fputc('\n', stderr);
#endif

  int i, i_local, index;
  double sign;
  for (i_local = 0; i_local < data->boundary_neumann_dm1->a0; ++i_local)
  {
    i = data->boundary_neumann_dm1->a1[i_local];
    index = m_cbd_dm1->cols_total[i];
    sign = m_cbd_dm1->values[index];
    data->g_neumann_dm1[i_local] *= sign;
  }

  matrix_sparse_mixed_constrained_linear_solve_with_diagonal_top_left_matrix(
    flux, temperature_on_cells,
    a, b, g, f, data->boundary_neumann_dm1, data->g_neumann_dm1);
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
g_dirichlet_0_big_free:
  free(g_dirichlet_0_big);
b_free:
  free(b->values);
  free(b);
a_free:
  free(a);
}
