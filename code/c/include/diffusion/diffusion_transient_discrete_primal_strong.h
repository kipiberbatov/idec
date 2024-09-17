#ifndef _diffusion_transient_discrete_primal_strong_h
#define _diffusion_transient_discrete_primal_strong_h

#include "double.h"
#include "mesh.h"

typedef struct diffusion_transient_discrete_primal_strong
{
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

void diffusion_transient_discrete_primal_strong_set_neumann_rows(
  matrix_sparse * lhs,
  const mesh * m,
  const jagged1 * boundary_neumann_discrete,
  const double * pi_1);

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

#endif /* _diffusion_transient_discrete_primal_strong_h */
