#include <errno.h>
#include "matrix_sparse_private.h"

matrix_sparse * matrix_sparse_linear_combination(
  const matrix_sparse * a, const matrix_sparse * b, double alpha, double beta)
{
  cs a0, b0;
  cs * res0;
  matrix_sparse * res = NULL;

  matrix_sparse_to_cs(&a0, a);
  matrix_sparse_to_cs(&b0, b);
  res0 = cs_add(&a0, &b0, alpha, beta);
  if (errno)
  {
    perror("Cannot find linear combination via cs_add");
    goto end;
  }
  res = (matrix_sparse *) malloc(sizeof(matrix_sparse));
  if (errno)
  {
    perror("Cannot allocate memory for a matrix_sparse object");
    goto res0_free;
  }
  matrix_sparse_from_cs(res, res0);
res0_free:
  free(res0);
end:
  return res;
}
