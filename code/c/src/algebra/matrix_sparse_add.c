#include <errno.h>
#include <stdio.h>
#include "matrix_sparse.h"

matrix_sparse * matrix_sparse_add(
  const matrix_sparse * a, const matrix_sparse * b)
{
  matrix_sparse * c;

  c = matrix_sparse_linear_combination(a, b, 1., 1.);
  if (errno)
  {
    perror("Cannot add matrices");
    return NULL;
  }
  return c;
}
