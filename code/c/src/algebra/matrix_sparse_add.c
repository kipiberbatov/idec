#include "color.h"
#include "matrix_sparse.h"

matrix_sparse * matrix_sparse_add(
  const matrix_sparse * a, const matrix_sparse * b)
{
  matrix_sparse * c;

  c = matrix_sparse_linear_combination(a, b, 1., 1.);
  if (c == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot add matrices\n", stderr);
  }
  return c;
}
