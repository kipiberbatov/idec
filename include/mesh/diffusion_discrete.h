#ifndef _diffusion_discrete_h
#define _diffusion_discrete_h

#include "mesh.h"

typedef struct diffusion_discrete
{
  double  * pi_0;
  double  * pi_1;
  double  * initial;
  double  * source;
  jagged1 * boundary_dirichlet;
  double  * g_dirichlet;
  jagged1 * boundary_neumann;
  double  * g_neumann;
} diffusion_discrete;

void diffusion_discrete_free(diffusion_discrete * data);

void diffusion_discrete_set_neumann_rows(
  matrix_sparse * lhs,
  const mesh * m,
  const jagged1 * boundary_neumann_discrete,
  const double * pi_1);

double * diffusion_discrete_solve_trapezoidal_method(
  const mesh * m,
  // const matrix_sparse * m_laplacian_0,
  const matrix_sparse * m_cbd_0,
  const matrix_sparse * m_cbd_star_1,
  const diffusion_discrete * data,
  double time_step,
  int number_of_steps);

#endif /* _diffusion_discrete_h */
