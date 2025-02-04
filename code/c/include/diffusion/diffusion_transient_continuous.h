#ifndef _diffusion_transient_continuous_h
#define _diffusion_transient_continuous_h

struct double_array_sequence_dynamic;
struct matrix_sparse;
struct mesh;

struct diffusion_transient_continuous
{
  double (*pi_0)(const double *);
  double (*kappa_1)(const double *);
  double (*initial)(const double *);
  double (*source)(const double *);
  int (*boundary_dirichlet)(const double *);
  double (*g_dirichlet)(const double *);
  int (*boundary_neumann)(const double *);
  double (*g_neumann)(const double *);
};

/******************************* primal strong ********************************/
double * diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal(
  const struct mesh * m,
  const struct matrix_sparse * m_cbd_0,
  const struct matrix_sparse * m_cbd_star_1,
  const struct diffusion_transient_continuous * data_continuous,
  double time_step,
  int number_of_steps);

struct double_array_sequence_dynamic *
diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal_to_steady_state(
  const struct mesh * m,
  const struct matrix_sparse * m_cbd_0,
  const struct matrix_sparse * m_cbd_star_1,
  const struct diffusion_transient_continuous * data_continuous,
  double time_step,
  double tolerance);

/******************************** primal weak *********************************/
double * diffusion_transient_continuous_primal_weak_cochain_solve_trapezoidal(
  const struct mesh * m,
  const double * m_vol_dm1,
  const double * m_vol_d,
  const double * m_inner_0,
  const double * m_inner_1,
  const struct diffusion_transient_continuous * data_continuous,
  double time_step,
  int number_of_steps);

struct double_array_sequence_dynamic *
diffusion_transient_continuous_primal_weak_cochain_solve_trapezoidal_to_steady_state(
  const struct mesh * m,
  const double * m_vol_dm1,
  const double * m_vol_d,
  const double * m_inner_0,
  const double * m_inner_1,
  const struct diffusion_transient_continuous * data_continuous,
  double time_step,
  double tolerance);

/******************************** mixed weak *********************************/
void diffusion_transient_continuous_mixed_weak_cochain_solve_trapezoidal(
  double * flow,
  double * potential,
  const struct mesh * m,
  const struct matrix_sparse * m_bd_d,
  const double * m_vol_dm1,
  const double * m_vol_d,
  const double * m_inner_0,
  const double * m_inner_dm1,
  const struct diffusion_transient_continuous * data_continuous,
  double time_step,
  int number_of_steps);

void
diffusion_transient_continuous_mixed_weak_cochain_solve_trapezoidal_to_steady_state(
  struct double_array_sequence_dynamic * flow,
  struct double_array_sequence_dynamic * potential,
  const struct mesh * m,
  const double * m_vol_dm1,
  const double * m_vol_d,
  const double * m_inner_0,
  const double * m_inner_dm1,
  const struct diffusion_transient_continuous * data_continuous,
  double time_step,
  double tolerance);

#endif /* _diffusion_transient_continuous_h */
