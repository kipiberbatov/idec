#include <errno.h>
#include <string.h>
#include "matrix_sparse_private.h"

void matrix_sparse_linear_solve(
  const matrix_sparse * a, double * b, const char * method)
{
  int i;
  
  for (i = 0; i < LINEAR_SOLVE_METHODS_TOTAL; ++i)
    if (!strcmp(method, linear_solve_methods[i]))
    {
      linear_solvers[i](a, b);
      if (errno)
      {
        perror("Unsuccessful linear solving");
        return;
      }
      return;
    }
  errno = EINVAL;
  perror(method);
  return;
}
