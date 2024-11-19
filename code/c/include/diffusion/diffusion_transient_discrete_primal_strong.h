#ifndef _diffusion_transient_discrete_primal_strong_h
#define _diffusion_transient_discrete_primal_strong_h

#include "double.h"
#include "diffusion_transient_continuous.h"

typedef struct diffusion_transient_discrete_primal_strong
{
  int number_of_cells_0;
  int number_of_cells_1;
  double  * pi_0;
  double  * pi_1;
  double  * initial;
  double  * source;
  jagged1 * boundary_dirichlet;
  double  * g_dirichlet;
  jagged1 * boundary_neumann;
  double  * g_neumann;
} diffusion_transient_discrete_primal_strong;

void diffusion_transient_discrete_primal_strong_free(
  diffusion_transient_discrete_primal_strong * data);

diffusion_transient_discrete_primal_strong *
diffusion_transient_discrete_primal_strong_from_continuous(
  const mesh * m,
  const diffusion_transient_continuous * data_continuous);

double * diffusion_transient_discrete_primal_strong_solve_trapezoidal(
  const mesh * m,
  const matrix_sparse * m_cbd_0,
  const matrix_sparse * m_cbd_star_1,
  const diffusion_transient_discrete_primal_strong * data,
  double time_step,
  int number_of_steps);

double_array_sequence_dynamic *
diffusion_transient_discrete_primal_strong_solve_trapezoidal_to_steady_state(
  const mesh * m,
  const matrix_sparse * m_cbd_0,
  const matrix_sparse * m_cbd_star_1,
  const diffusion_transient_discrete_primal_strong * data,
  double time_step,
  double tolerance);

void diffusion_transient_discrete_primal_strong_file_print_raw(
  FILE * out,
  const diffusion_transient_discrete_primal_strong * data);

diffusion_transient_discrete_primal_strong *
diffusion_transient_discrete_primal_strong_file_scan_raw(FILE * in);

#endif /* _diffusion_transient_discrete_primal_strong_h */
