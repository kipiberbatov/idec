#include "matrix_sparse_private.h"

/* find x := l^{-T} x, where l is lower triangular */
void matrix_sparse_lower_triangular_transpose_linear_solve(
  double * x, const matrix_sparse * l)
{
  cs l0;

  matrix_sparse_to_cs(&l0, l);
  cs_ltsolve(&l0, x);
}
