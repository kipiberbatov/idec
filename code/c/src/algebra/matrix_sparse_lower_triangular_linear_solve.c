#include "matrix_sparse_private.h"

/* find x := l^{-1} x, where l is lower triangular */
void matrix_sparse_lower_triangular_linear_solve(
  double * x, const matrix_sparse * l)
{
  cs l0;

  matrix_sparse_to_cs(&l0, l);
  cs_lsolve(&l0, x);
}
