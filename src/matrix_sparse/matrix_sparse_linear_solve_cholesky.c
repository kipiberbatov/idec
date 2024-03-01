#include <errno.h>
#include <string.h>
#include "matrix_sparse_private.h"

void matrix_sparse_linear_solve_cholesky(const matrix_sparse * a, double * b)
{
  int correct;
  cs a0;
  
  matrix_sparse_to_cs(&a0, a);
  correct = cs_cholsol(1, &a0, b);
  if (!correct)
  {
    errno = EINVAL;
    fputs("matrix_sparse_linear_solve_cholesky - cannot solve linear system\n",
          stderr);
    return;
  }
}
