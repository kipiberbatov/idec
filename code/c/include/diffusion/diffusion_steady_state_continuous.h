#ifndef _diffusion_steady_state_continuous_h
#define _diffusion_steady_state_continuous_h

#include "diffusion_steady_state_discrete.h"

typedef int region_implicit(const double *);

typedef struct diffusion_steady_state_continuous
{
  scalar_field pi_0;
  scalar_field pi_1;
  scalar_field source;
  region_implicit * boundary_dirichlet;
  scalar_field g_dirichlet;
  region_implicit * boundary_neumann;
  scalar_field g_neumann;
} diffusion_steady_state_continuous;

diffusion_steady_state_discrete * diffusion_steady_state_continuous_discretize(
  const mesh * m,
  const diffusion_steady_state_continuous * data_continuous);

double * diffusion_steady_state_continuous_solve(
  const mesh * m,
  const matrix_sparse * m_cbd_0,
  const matrix_sparse * m_cbd_star_1,
  const diffusion_steady_state_continuous * data_continuous);

double * diffusion_steady_state_continuous_primal_weak_solve(
  const mesh * m,
  const double * m_vol_dm1,
  const double * m_inner_1,
  const diffusion_steady_state_continuous * data_continuous);

#endif /* _diffusion_steady_state_continuous_h */
