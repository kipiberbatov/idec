#ifndef _diffusion_transient_discrete_mixed_weak_h
#define _diffusion_transient_discrete_mixed_weak_h

#include <stdio.h>

struct diffusion_transient_continuous;
struct double_array_sequence_dynamic;
struct jagged1;
struct matrix_sparse;
struct mesh;

struct diffusion_transient_discrete_mixed_weak
{
  int number_of_cells_dm1;
  int number_of_cells_d;
  double * pi_d;
  double * kappa_dm1;
  double * initial_dual_potential;
  double * initial_flow;
  double * source;
  struct jagged1 * boundary_dirichlet_dm1;
  struct jagged1 * boundary_dirichlet_0;
  double * g_dirichlet_0;
  struct jagged1 * boundary_neumann_dm1;
  double * g_neumann_dm1;
};

void diffusion_transient_discrete_mixed_weak_free(
  struct diffusion_transient_discrete_mixed_weak * data);

struct diffusion_transient_discrete_mixed_weak *
diffusion_transient_discrete_mixed_weak_from_continuous(
  const struct mesh * m,
  const double * m_vol_dm1,
  const double * m_vol_d,
  const struct matrix_sparse * m_cbd_star_d,
  const struct diffusion_transient_continuous * data_continuous);

void diffusion_transient_discrete_mixed_weak_solve_trapezoidal(
  double * flow,
  double * dual_potential,
  const struct mesh * m,
  const struct matrix_sparse * m_cbd_dm1,
  const double * m_inner_dm1,
  const double * m_inner_d,
  const struct diffusion_transient_discrete_mixed_weak * data,
  double time_step,
  int number_of_steps);


void diffusion_transient_discrete_mixed_weak_solve_trapezoidal_to_steady_state(
  struct double_array_sequence_dynamic * flow,
  struct double_array_sequence_dynamic * dual_potential,
  const struct mesh * m,
  const double * m_inner_0,
  const double * m_inner_dm1,
  const struct diffusion_transient_discrete_mixed_weak * data,
  double time_step,
  double tolerance);


void diffusion_transient_discrete_mixed_weak_file_print_raw(
  FILE * out,
  const struct diffusion_transient_discrete_mixed_weak * data);

struct diffusion_transient_discrete_mixed_weak *
diffusion_transient_discrete_mixed_weak_file_scan_raw(FILE * in);

#endif /* _diffusion_transient_discrete_mixed_weak_h */
