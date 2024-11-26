#ifndef _diffusion_steady_state_continuous_h
#define _diffusion_steady_state_continuous_h

#include "mesh.h"

typedef int region_implicit(const double *);

typedef struct diffusion_steady_state_continuous
{
  scalar_field kappa_1;
  scalar_field source;
  region_implicit * boundary_dirichlet;
  scalar_field g_dirichlet;
  region_implicit * boundary_neumann;
  scalar_field g_neumann;
} diffusion_steady_state_continuous;

/******************************* primal strong ********************************/
double * diffusion_steady_state_continuous_primal_strong_cochain_solve(
  const mesh * m,
  const matrix_sparse * m_cbd_0,
  const matrix_sparse * m_cbd_star_1,
  const diffusion_steady_state_continuous * data_continuous);

/******************************** primal weak *********************************/
double * diffusion_steady_state_continuous_primal_weak_cochain_solve(
  const mesh * m,
  const double * m_vol_dm1,
  const double * m_vol_d,
  const double * m_inner_1,
  const diffusion_steady_state_continuous * data_continuous);

/******************************** mixed weak *********************************/
void diffusion_steady_state_continuous_mixed_weak_cochain_solve(
  double * flow,
  double * dual_potential,
  const mesh * m,
  const matrix_sparse * m_bd_d,
  const double * m_vol_dm1,
  const double * m_vol_d,
  const double * m_inner_dm1,
  const double * m_inner_d,
  const diffusion_steady_state_continuous * data_continuous);

#endif /* _diffusion_steady_state_continuous_h */
