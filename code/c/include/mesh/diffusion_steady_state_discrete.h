#ifndef _diffusion_steady_state_discrete_h
#define _diffusion_steady_state_discrete_h

#include "double.h"
#include "mesh.h"

typedef struct diffusion_steady_state_discrete
{
  double  * pi_0;
  double  * pi_1;
  double  * source;
  jagged1 * boundary_dirichlet;
  double  * g_dirichlet;
  jagged1 * boundary_neumann;
  double  * g_neumann;
} diffusion_steady_state_discrete;

void
diffusion_steady_state_discrete_free(diffusion_steady_state_discrete * data);

double * diffusion_steady_state_discrete_solve(
  const mesh * m,
  const matrix_sparse * m_cbd_0,
  const matrix_sparse * m_cbd_star_1,
  const diffusion_steady_state_discrete * data);

#endif /* _diffusion_steady_state_discrete_h */
