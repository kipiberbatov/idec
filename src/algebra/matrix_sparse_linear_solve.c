#include <errno.h>
#include <string.h>
#include "matrix_sparse_private.h"

void matrix_sparse_linear_solve(
  const matrix_sparse * a, double * b, const char * method)
{
  if (!strcmp(method, "--cholesky"))
    matrix_sparse_linear_solve_cholesky(a, b);
  else if (!strcmp(method, "--lu"))
    matrix_sparse_linear_solve_lu(a, b);
  else
  {
    errno = EINVAL;
    fprintf(stderr,
      "matrix_sparse_linear_solve - method %s is not supported\n", method);
    return;
  }
  
  if (errno)
    fputs("matrix_sparse_linear_solve - cannot solve linear system\n", stderr);
}
