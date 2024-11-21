#ifndef _diffusion_steady_state_discrete_dual_flow_from_potential_h
#define _diffusion_steady_state_discrete_dual_flow_from_potential_h

#include "mesh.h"

void diffusion_steady_state_discrete_dual_flow_from_potential(
  double * dual_flow,
  const mesh * m,
  const matrix_sparse * m_bd_1,
  const double * pi_1,
  const double * potential);

#endif /* _diffusion_steady_state_discrete_dual_flow_from_potential_h */
