#ifndef _diffusion_transient_discrete_primal_weak_h
#define _diffusion_transient_discrete_primal_weak_h

#include <stdio.h>

struct diffusion_transient_continuous;
struct double_array_sequence_dynamic;
struct jagged1;
struct matrix_sparse;
struct mesh;

struct diffusion_transient_discrete_primal_weak
{
  int number_of_cells_0;
  int number_of_cells_1;
  int number_of_cells_d;
  double * pi_0;
  double * kappa_1;
  double * initial;
  double * source;
  struct jagged1 * boundary_dirichlet;
  double * g_dirichlet;
  struct jagged1 * boundary_neumann;
  double * g_neumann;
};

struct diffusion_transient_discrete_primal_weak *
diffusion_transient_discrete_primal_weak_from_continuous(
  const struct mesh * m,
  const double * m_vol_dm1,
  const double * m_vol_d,
  const struct diffusion_transient_continuous * data_continuous);

void diffusion_transient_discrete_primal_weak_free(
  struct diffusion_transient_discrete_primal_weak * data);

double * diffusion_transient_discrete_primal_weak_solve_trapezoidal(
  const struct mesh * m,
  const double * m_inner_0,
  const double * m_inner_1,
  const struct diffusion_transient_discrete_primal_weak * data,
  double time_step,
  int number_of_steps);

struct double_array_sequence_dynamic *
diffusion_transient_discrete_primal_weak_solve_trapezoidal_to_steady_state(
  const struct mesh * m,
  const double * m_inner_0,
  const double * m_inner_1,
  const struct diffusion_transient_discrete_primal_weak * data,
  double time_step,
  double tolerance);

void diffusion_transient_discrete_primal_weak_file_print_raw(
  FILE * out,
  const struct diffusion_transient_discrete_primal_weak * data);

struct diffusion_transient_discrete_primal_weak *
diffusion_transient_discrete_primal_weak_file_scan_raw(FILE * in);

#endif /* _diffusion_transient_discrete_primal_weak_h */
