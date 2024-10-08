#ifndef _diffusion_transient_continuous_h
#define _diffusion_transient_continuous_h

#include "double.h"
#include "mesh.h"

/* typedef double scalar_field(const double *); */
typedef int region_implicit(const double *);

typedef struct diffusion_transient_continuous
{
  scalar_field pi_0;
  scalar_field pi_1;
  scalar_field initial;
  scalar_field source;
  region_implicit * boundary_dirichlet;
  scalar_field g_dirichlet;
  region_implicit * boundary_neumann;
  scalar_field g_neumann;
} diffusion_transient_continuous;

/******************************* primal strong ********************************/
double * diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal(
  const mesh * m,
  const matrix_sparse * m_cbd_0,
  const matrix_sparse * m_cbd_star_1,
  const diffusion_transient_continuous * data_continuous,
  double time_step,
  int number_of_steps);

double_array_sequence_dynamic *
diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal_to_steady_state(
  const mesh * m,
  const matrix_sparse * m_cbd_0,
  const matrix_sparse * m_cbd_star_1,
  const diffusion_transient_continuous * data_continuous,
  double time_step,
  double tolerance);

/******************************** primal weak *********************************/
double * diffusion_transient_continuous_primal_weak_cochain_solve_trapezoidal(
  const mesh * m,
  const double * m_vol_dm1,
  const double * m_vol_d,
  const double * m_inner_0,
  const double * m_inner_1,
  const diffusion_transient_continuous * data_continuous,
  double time_step,
  int number_of_steps);

double_array_sequence_dynamic *
diffusion_transient_continuous_primal_weak_cochain_solve_trapezoidal_to_steady_state(
  const mesh * m,
  const double * m_vol_dm1,
  const double * m_vol_d,
  const double * m_inner_0,
  const double * m_inner_1,
  const diffusion_transient_continuous * data_continuous,
  double time_step,
  double tolerance);

/******************************** mixed weak *********************************/
void diffusion_transient_continuous_mixed_weak_cochain_solve_trapezoidal(
  double * flux,
  double * temperature,
  const mesh * m,
  const matrix_sparse * m_bd_d,
  const double * m_vol_dm1,
  const double * m_vol_d,
  const double * m_inner_0,
  const double * m_inner_dm1,
  const diffusion_transient_continuous * data_continuous,
  double time_step,
  int number_of_steps);

void
diffusion_transient_continuous_mixed_weak_cochain_solve_trapezoidal_to_steady_state(
  double_array_sequence_dynamic * flux,
  double_array_sequence_dynamic * temperature,
  const mesh * m,
  const double * m_vol_dm1,
  const double * m_vol_d,
  const double * m_inner_0,
  const double * m_inner_dm1,
  const diffusion_transient_continuous * data_continuous,
  double time_step,
  double tolerance);

#endif /* _diffusion_transient_continuous_h */
