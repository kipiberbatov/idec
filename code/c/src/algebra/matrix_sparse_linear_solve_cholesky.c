#include <errno.h>
#include <string.h>

#include "color.h"
#include "matrix_sparse_private.h"

void matrix_sparse_linear_solve_cholesky(const matrix_sparse * a, double * b)
{
  int correct;
  cs a0;

  matrix_sparse_to_cs(&a0, a);
  correct = cs_cholsol(1, &a0, b);
  if (!correct)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot solve linear system\n", stderr);
    errno = EINVAL;
    return;
  }
  else
    errno = 0;
}
