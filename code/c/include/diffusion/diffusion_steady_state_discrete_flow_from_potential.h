#ifndef _diffusion_steady_state_discrete_flow_from_potential_h
#define _diffusion_steady_state_discrete_flow_from_potential_h

#include "mesh.h"

void diffusion_steady_state_discrete_flow_from_potential(
  double * flow,
  const mesh * m,
  const matrix_sparse * m_bd_1,
  const double * kappa_1,
  const double * potential,
  const matrix_sparse * m_hodge_1);

#endif /* _diffusion_steady_state_discrete_flow_from_potential_h */
