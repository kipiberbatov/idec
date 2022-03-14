#include <errno.h>
#include <string.h>
#include "matrix_sparse_private.h"

void matrix_sparse_linear_solve_cholesky(const matrix_sparse * a, double * b)
{
  cs a0;
  
  matrix_sparse_to_cs(&a0, a);
  cs_cholsol(1, &a0, b);
  if (errno)
  {
    perror("Cannot solve linear system via cs_cholsol");
    return;
  }
}
