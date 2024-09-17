#ifndef _diffusion_transient_discrete_primal_weak_h
#define _diffusion_transient_discrete_primal_weak_h

#include "diffusion_transient_continuous.h"

typedef struct diffusion_transient_discrete_primal_weak
{
  double  * pi_0;
  double  * pi_1;
  double  * initial;
  double  * source;
  jagged1 * boundary_dirichlet;
  double  * g_dirichlet;
  jagged1 * boundary_neumann;
  double  * g_neumann;
} diffusion_transient_discrete_primal_weak;

diffusion_transient_discrete_primal_weak *
diffusion_transient_discrete_primal_weak_from_continuous(
  const mesh * m,
  const double * m_vol_dm1,
  const double * m_vol_d,
  const diffusion_transient_continuous * data_continuous);

void diffusion_transient_discrete_primal_weak_free(
  diffusion_transient_discrete_primal_weak * data);

double * diffusion_transient_discrete_primal_weak_solve_trapezoidal(
  const mesh * m,
  const double * m_inner_0,
  const double * m_inner_1,
  const diffusion_transient_discrete_primal_weak * data,
  double time_step,
  int number_of_steps);

#endif /* _diffusion_transient_discrete_primal_weak_h */
