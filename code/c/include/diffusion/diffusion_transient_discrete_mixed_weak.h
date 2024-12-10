#ifndef _diffusion_transient_discrete_mixed_weak_h
#define _diffusion_transient_discrete_mixed_weak_h

#include "diffusion_transient_continuous.h"

typedef struct diffusion_transient_discrete_mixed_weak
{
  int number_of_cells_dm1;
  int number_of_cells_d;
  double  * pi_d;
  double  * kappa_dm1;
  double  * initial_dual_potential;
  double  * initial_flow;
  double  * source;
  jagged1 * boundary_dirichlet_dm1;
  jagged1 * boundary_dirichlet_0;
  double  * g_dirichlet_0;
  jagged1 * boundary_neumann_dm1;
  double  * g_neumann_dm1;
} diffusion_transient_discrete_mixed_weak;

void diffusion_transient_discrete_mixed_weak_free(
  diffusion_transient_discrete_mixed_weak * data);

diffusion_transient_discrete_mixed_weak *
diffusion_transient_discrete_mixed_weak_from_continuous(
  const mesh * m,
  const double * m_vol_dm1,
  const double * m_vol_d,
  const matrix_sparse * m_cbd_star_d,
  const diffusion_transient_continuous * data_continuous);

void diffusion_transient_discrete_mixed_weak_solve_trapezoidal(
  double * flow,
  double * dual_potential,
  const mesh * m,
  const matrix_sparse * m_cbd_dm1,
  const double * m_inner_dm1,
  const double * m_inner_d,
  const diffusion_transient_discrete_mixed_weak * data,
  double time_step,
  int number_of_steps);

/*
void diffusion_transient_discrete_mixed_weak_solve_trapezoidal_to_steady_state(
  double_array_sequence_dynamic * flow,
  double_array_sequence_dynamic * dual_potential,
  const mesh * m,
  const double * m_inner_0,
  const double * m_inner_dm1,
  const diffusion_transient_discrete_mixed_weak * data,
  double time_step,
  double tolerance);
*/

void diffusion_transient_discrete_mixed_weak_file_print_raw(
  FILE * out,
  const diffusion_transient_discrete_mixed_weak * data);

diffusion_transient_discrete_mixed_weak *
diffusion_transient_discrete_mixed_weak_file_scan_raw(FILE * in);

#endif /* _diffusion_transient_discrete_mixed_weak_h */
