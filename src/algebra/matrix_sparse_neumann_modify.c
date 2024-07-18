#include "matrix_sparse.h"

static double double_array_total_sum(int n, const double * a)
{
  int i;
  double result;

  result = 0;
  for (i = 0; i < n; ++i)
    result += a[i];
  return result;
}

void matrix_sparse_neumann_modify(
  matrix_sparse * lhs,
  int i,
  int size_i,
  const int * neighbors,
  const double * coefficients)
{
  int i0, j_local;
  double * position;
  
  /* off-diagonal elements */
  for (j_local = 0; j_local < size_i; ++j_local)
  {
    i0 = neighbors[j_local];
    position = matrix_sparse_part_pointer(lhs, i, i0);
    *position = -coefficients[j_local];
  }

  /* diagonal element */
  position = matrix_sparse_part_pointer(lhs, i, i);
  *position = double_array_total_sum(size_i, coefficients);
}
