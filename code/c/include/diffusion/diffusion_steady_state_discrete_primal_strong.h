#ifndef _diffusion_steady_state_discrete_primal_strong_h
#define _diffusion_steady_state_discrete_primal_strong_h

#include "diffusion_steady_state_continuous.h"

typedef struct diffusion_steady_state_discrete_primal_strong
{
  int number_of_cells_1;
  int number_of_cells_0;
  double  * kappa_1;
  double  * source;
  jagged1 * boundary_dirichlet;
  double  * g_dirichlet;
  jagged1 * boundary_neumann;
  double  * g_neumann;
} diffusion_steady_state_discrete_primal_strong;

void diffusion_steady_state_discrete_primal_strong_free(
  diffusion_steady_state_discrete_primal_strong * data);

diffusion_steady_state_discrete_primal_strong *
diffusion_steady_state_discrete_primal_strong_from_continuous(
  const mesh * m,
  const diffusion_steady_state_continuous * data_continuous);

double * diffusion_steady_state_discrete_primal_strong_solve(
  const mesh * m,
  const matrix_sparse * m_cbd_0,
  const matrix_sparse * m_cbd_star_1,
  const diffusion_steady_state_discrete_primal_strong * data);

void diffusion_steady_state_discrete_primal_strong_file_print_raw(
  FILE * out,
  const diffusion_steady_state_discrete_primal_strong * data);

diffusion_steady_state_discrete_primal_strong *
diffusion_steady_state_discrete_primal_strong_file_scan_raw(FILE * in);

#endif /* _diffusion_steady_state_discrete_primal_strong_h */
