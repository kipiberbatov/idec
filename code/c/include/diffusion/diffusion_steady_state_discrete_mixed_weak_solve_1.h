#ifndef _diffusion_steady_state_discrete_mixed_weak_solve_1_h
#define _diffusion_steady_state_discrete_mixed_weak_solve_1_h

struct diffusion_steady_state_discrete;
struct mesh;
struct matrix_sparse;

void diffusion_steady_state_discrete_mixed_weak_solve_1(
  double * flow_rate,
  double * dual_potential,
  const struct mesh * m,
  const struct matrix_sparse * m_cbd_dm1,
  const double * m_inner_dm1,
  const double * m_inner_d,
  const struct diffusion_steady_state_discrete * data);

#endif /* _diffusion_steady_state_discrete_mixed_weak_solve_1_h */
