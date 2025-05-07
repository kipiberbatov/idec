#ifndef _diffusion_steady_state_discrete_primal_weak_solve_1_h
#define _diffusion_steady_state_discrete_primal_weak_solve_1_h

struct diffusion_steady_state_discrete;
struct mesh;

void diffusion_steady_state_discrete_primal_weak_solve_1(
  double ** potential,
  int * status,
  const struct mesh * m,
  const double * m_inner_1,
  const struct diffusion_steady_state_discrete * data);

#endif /* _diffusion_steady_state_discrete_primal_weak_solve_1_h */
