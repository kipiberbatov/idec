#ifndef _diffusion_steady_state_continuous_h
#define _diffusion_steady_state_continuous_h

struct matrix_sparse;
struct mesh;

struct diffusion_steady_state_continuous
{
  double (*kappa_1)(const double *);
  double (*source)(const double *);
  int (*boundary_dirichlet)(const double *);
  double (*g_dirichlet)(const double *);
  int (*boundary_neumann)(const double *);
  double (*g_neumann)(const double *);
};

/******************************* primal strong ********************************/
double * diffusion_steady_state_continuous_primal_strong_cochain_solve(
  const struct mesh * m,
  const struct matrix_sparse * m_cbd_0,
  const struct matrix_sparse * m_cbd_star_1,
  const struct diffusion_steady_state_continuous * data_continuous);

/******************************** primal weak *********************************/
double * diffusion_steady_state_continuous_primal_weak_cochain_solve(
  const struct mesh * m,
  const double * m_vol_dm1,
  const double * m_vol_d,
  const double * m_inner_1,
  const struct diffusion_steady_state_continuous * data_continuous);

/******************************** mixed weak *********************************/
void diffusion_steady_state_continuous_mixed_weak_cochain_solve(
  double * flow_rate,
  double * dual_potential,
  const struct mesh * m,
  const struct matrix_sparse * m_bd_d,
  const double * m_vol_dm1,
  const double * m_vol_d,
  const double * m_inner_dm1,
  const double * m_inner_d,
  const struct diffusion_steady_state_continuous * data_continuous);

#endif /* _diffusion_steady_state_continuous_h */
