#ifndef _diffusion_steady_state_discrete_mixed_weak_h
#define _diffusion_steady_state_discrete_mixed_weak_h

#include "diffusion_steady_state_continuous.h"
#include "mesh.h"

typedef struct diffusion_steady_state_discrete_mixed_weak
{
  int number_of_cells_dm1;
  int number_of_cells_d;
  double  * kappa_dm1;
  double  * source_d;
  jagged1 * boundary_dirichlet_dm1;
  jagged1 * boundary_dirichlet_0;
  double  * g_dirichlet_0;
  jagged1 * boundary_neumann_dm1;
  double  * g_neumann_dm1;
} diffusion_steady_state_discrete_mixed_weak;

void diffusion_steady_state_discrete_mixed_weak_free(
  diffusion_steady_state_discrete_mixed_weak * data);

diffusion_steady_state_discrete_mixed_weak *
diffusion_steady_state_discrete_mixed_weak_from_continuous(
  const mesh * m,
  const double * m_vol_dm1,
  const double * m_vol_d,
  const diffusion_steady_state_continuous * data_continuous);

void diffusion_steady_state_discrete_mixed_weak_solve(
  double * flow,
  double * dual_potential,
  const mesh * m,
  const matrix_sparse * m_bd_d,
  const double * m_inner_dm1,
  const double * m_inner_d,
  const diffusion_steady_state_discrete_mixed_weak * data);

void diffusion_steady_state_discrete_mixed_weak_file_print_raw(
  FILE * out,
  const diffusion_steady_state_discrete_mixed_weak * data);

diffusion_steady_state_discrete_mixed_weak *
diffusion_steady_state_discrete_mixed_weak_file_scan_raw(FILE * in);

#endif /* _diffusion_steady_state_discrete_mixed_weak_h */
