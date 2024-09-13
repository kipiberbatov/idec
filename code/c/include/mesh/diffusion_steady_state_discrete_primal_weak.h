#ifndef _diffusion_steady_state_discrete_primal_weak_h
#define _diffusion_steady_state_discrete_primal_weak_h

#include "diffusion_steady_state_continuous.h"
#include "mesh.h"

typedef struct diffusion_steady_state_discrete_primal_weak
{
  double  * pi_0;
  double  * pi_1;
  double  * source;
  jagged1 * boundary_dirichlet;
  double  * g_dirichlet;
  jagged1 * boundary_neumann;
  double  * g_neumann;
} diffusion_steady_state_discrete_primal_weak;

diffusion_steady_state_discrete_primal_weak *
diffusion_steady_state_discrete_primal_weak_from_continuous(
  const mesh * m,
  const double * m_vol,
  const diffusion_steady_state_continuous * data_continuous);

void diffusion_steady_state_discrete_primal_weak_free(
  diffusion_steady_state_discrete_primal_weak * data);

double * diffusion_steady_state_discrete_primal_weak_solve(
  const mesh * m,
  const double * m_inner_1,
  const diffusion_steady_state_discrete_primal_weak * data);

#endif /* _diffusion_steady_state_discrete_primal_weak_h */
