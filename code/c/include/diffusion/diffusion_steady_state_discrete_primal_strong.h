#ifndef _diffusion_steady_state_discrete_primal_strong_h
#define _diffusion_steady_state_discrete_primal_strong_h

#include "mesh.h"

typedef struct diffusion_steady_state_discrete_primal_strong
{
  double  * pi_0;
  double  * pi_1;
  double  * source;
  jagged1 * boundary_dirichlet;
  double  * g_dirichlet;
  jagged1 * boundary_neumann;
  double  * g_neumann;
} diffusion_steady_state_discrete_primal_strong;

void diffusion_steady_state_discrete_primal_strong_free(
  diffusion_steady_state_discrete_primal_strong * data);

double * diffusion_steady_state_discrete_primal_strong_solve(
  const mesh * m,
  const matrix_sparse * m_cbd_0,
  const matrix_sparse * m_cbd_star_1,
  const diffusion_steady_state_discrete_primal_strong * data);

#endif /* _diffusion_steady_state_discrete_primal_strong_h */
