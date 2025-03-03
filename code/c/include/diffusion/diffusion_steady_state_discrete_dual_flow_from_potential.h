#ifndef _diffusion_steady_state_discrete_dual_flow_from_potential_h
#define _diffusion_steady_state_discrete_dual_flow_from_potential_h

struct matrix_sparse;
struct mesh;

void diffusion_steady_state_discrete_dual_flow_from_potential(
  double * dual_flow,
  const struct mesh * m,
  const struct matrix_sparse * m_bd_1,
  const double * kappa_1,
  const double * potential);

#endif /* _diffusion_steady_state_discrete_dual_flow_from_potential_h */
