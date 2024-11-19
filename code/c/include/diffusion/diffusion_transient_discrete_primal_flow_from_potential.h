#ifndef _diffusion_transient_discrete_primal_flow_from_potential_h
#define _diffusion_transient_discrete_primal_flow_from_potential_h

#include "mesh.h"

void diffusion_transient_discrete_primal_flow_from_potential(
  double * flow,
  const mesh * m,
  const matrix_sparse * m_bd_1,
  const double * pi_1,
  const double * potential,
  const matrix_sparse * m_hodge_1,
  int number_of_steps);

#endif /* _diffusion_transient_discrete_primal_flow_from_potential_h */
