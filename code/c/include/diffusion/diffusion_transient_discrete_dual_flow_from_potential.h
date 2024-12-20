#ifndef _diffusion_transient_discrete_dual_flow_from_potential_h
#define _diffusion_transient_discrete_dual_flow_from_potential_h

#include "mesh.h"

void diffusion_transient_discrete_dual_flow_from_potential(
  double * dual_flow,
  const mesh * m,
  const matrix_sparse * m_bd_1,
  const double * kappa_1,
  int number_of_steps,
  const double * potential);

#endif /* _diffusion_transient_discrete_dual_flow_from_potential_h */
