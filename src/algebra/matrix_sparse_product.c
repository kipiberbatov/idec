#include <errno.h>
#include "matrix_sparse_private.h"

matrix_sparse * matrix_sparse_product(
  const matrix_sparse * a, const matrix_sparse * b)
{
  cs a0, b0;
  cs * res0;
  matrix_sparse * res = NULL;
  
  matrix_sparse_to_cs(&a0, a);
  matrix_sparse_to_cs(&b0, b);
  
  res0 = cs_multiply(&a0, &b0);
  if (res0 == NULL)
  {
    perror("Cannot find matrix product via cs_multiply");
    goto end;
  }
  errno = 0;
  
  res = (matrix_sparse *) malloc(sizeof(matrix_sparse));
  if (res == NULL)
  {
    perror("Cannot allocate memory for a matrix_sparse object");
    goto res0_free;
  }
  errno = 0;
  
  matrix_sparse_from_cs(res, res0);

res0_free:
  free(res0);
end:
  return res;
}
