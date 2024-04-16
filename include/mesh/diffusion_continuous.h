#ifndef _diffusion_continuous_h
#define _diffusion_continuous_h

#include "diffusion_discrete.h"

typedef int region_implicit(const double *);

typedef struct diffusion_continuous
{
  scalar_field pi_0;
  scalar_field pi_1;
  scalar_field initial;
  scalar_field source;
  region_implicit * boundary_dirichlet;
  scalar_field g_dirichlet;
  region_implicit * boundary_neumann;
  scalar_field g_neumann;
} diffusion_continuous;

diffusion_discrete * diffusion_continuous_discretize(
  const mesh * m,
  const diffusion_continuous * data_continuous);

double * diffusion_continuous_solve_trapezoidal_method(
  const mesh * m,
  const matrix_sparse * m_cbd_0,
  const matrix_sparse * m_cbd_star_1,
  const diffusion_continuous * data_continuous,
  double time_step,
  int number_of_steps);

double_array_sequence_dynamic *
diffusion_continuous_solve_trapezoidal_method_to_steady_state(
  const mesh * m,
  const matrix_sparse * m_cbd_0,
  const matrix_sparse * m_cbd_star_1,
  const diffusion_continuous * data_continuous,
  double time_step);

#endif /* _diffusion_continuous_h */
