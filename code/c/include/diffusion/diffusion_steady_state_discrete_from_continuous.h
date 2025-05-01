#ifndef _diffusion_steady_state_discrete_from_continuous_h
#define _diffusion_steady_state_discrete_from_continuous_h

struct diffusion_steady_state_continuous;
struct diffusion_steady_state_discrete;
struct diffusion_steady_state_discrete_pre_processing;
struct jagged1;
struct mesh;

void diffusion_steady_state_discrete_from_continuous(
  struct diffusion_steady_state_discrete ** result,
  int * status,
  const struct mesh * m,
  const struct jagged1 * m_boundary_dm1,
  const double * m_vol_dm1,
  const double * m_vol_d,
  const struct diffusion_steady_state_continuous * data_continuous,
  const struct diffusion_steady_state_discrete_pre_processing * functions);

#endif /* _diffusion_steady_state_discrete_from_continuous_h */
