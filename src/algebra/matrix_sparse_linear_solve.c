#include <errno.h>
#include <string.h>
#include "matrix_sparse_private.h"

void matrix_sparse_linear_solve(
  const matrix_sparse * a, double * b, const char * method)
{
  int i;
  
  for (i = 0; i < MATRIX_SPARSE_LINEAR_SOLVE_METHOD_TOTAL; ++i)
    if (!strcmp(method, matrix_sparse_linear_solve_method[i]))
    {
      matrix_sparse_linear_solve_function[i](a, b);
      if (errno)
      {
        fputs("matrix_sparse_linear_solve - cannot solve equation\n", stderr);
        return;
      }
      return;
    }
  errno = EINVAL;
  fprintf(stderr, "matrix_sparse_linear_solve - method %s is not supported\n",
          method);
  return;
}
