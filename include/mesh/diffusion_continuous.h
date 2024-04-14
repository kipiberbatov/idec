#ifndef _diffusion_continuous_h
#define _diffusion_continuous_h

#include "diffusion_discrete.h"
#include "mesh.h"

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
  // const matrix_sparse * m_laplacian_0,
  const matrix_sparse * m_cbd_0,
  const matrix_sparse * m_cbd_star_1,
  const diffusion_continuous * data,
  double time_step,
  int number_of_steps);

#endif /* _diffusion_continuous_h */
