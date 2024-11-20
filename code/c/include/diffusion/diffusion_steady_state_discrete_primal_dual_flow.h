#ifndef _diffusion_steady_state_discrete_primal_dual_flow_h
#define _diffusion_steady_state_discrete_primal_dual_flow_h

#include "mesh.h"

void diffusion_steady_state_discrete_primal_dual_flow(
  double * dual_flow,
  const mesh * m,
  const matrix_sparse * m_bd_1,
  const double * pi_1,
  const double * potential);

#endif /* _diffusion_steady_state_discrete_primal_dual_flow_h */
