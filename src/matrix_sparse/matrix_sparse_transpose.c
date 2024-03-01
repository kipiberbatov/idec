#include <errno.h>
#include "matrix_sparse_private.h"

matrix_sparse * matrix_sparse_transpose(const matrix_sparse * a)
{
  cs a0;
  cs * b0;
  matrix_sparse * b = NULL;
  
  matrix_sparse_to_cs(&a0, a);
  b0 = cs_transpose(&a0, 1);
  if (errno)
  {
    perror("Cannot find transpose via cs_transpose");
    goto end;
  }
  b = (matrix_sparse *) malloc(sizeof(matrix_sparse));
  if (errno)
  {
    perror("Cannot allocate memory for a matrix_sparse object");
    goto b0_free;
  }
  matrix_sparse_from_cs(b, b0);
b0_free:
  free(b0);
end:
  return b;
}
