#include <errno.h>
#include <string.h>

#include "diffusion_transient_discrete_primal_weak_solve_trapezoidal_next.h"

void diffusion_transient_discrete_primal_weak_solve_trapezoidal_next(
  double * next,
  double * rhs_final,
  const double * current,
  const matrix_sparse * lhs,
  const matrix_sparse * rhs,
  const double * free_part,
  const diffusion_transient_discrete_primal_weak * data)
{
  /* $rhs_final = free_part + rhs * current$ */
  memcpy(rhs_final, free_part, sizeof(double) * lhs->rows);
  matrix_sparse_vector_multiply_add(rhs_final, rhs, current);

  /* update Dirichlet rows of rhs_final by Dirichlet boundary conditions */
  double_array_substitute_inverse(
    rhs_final,
    data->boundary_dirichlet->a0,
    data->g_dirichlet, 
    data->boundary_dirichlet->a1);

  /* $next = lhs^{-1} . rhs_final$ */
  memcpy(next, rhs_final, sizeof(double) * lhs->rows);
  matrix_sparse_linear_solve(lhs, next, "--lu");
  if (errno)
  {
    fprintf(stderr, "%s:%d: cannot solve linear system\n", __FILE__, __LINE__);
    return;
  }
}
