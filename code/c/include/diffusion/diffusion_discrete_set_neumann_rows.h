#ifndef _diffusion_discrete_set_neumann_rows_h
#define _diffusion_discrete_set_neumann_rows_h

#include "mesh.h"

void diffusion_discrete_set_neumann_rows(
  matrix_sparse * lhs,
  const mesh * m,
  const jagged1 * boundary_neumann_discrete,
  const double * kappa_1);

#endif /* _diffusion_discrete_set_neumann_rows_h */
