#include <errno.h>
#include "matrix_sparse_private.h"

void matrix_sparse_fprint_matrix_form_raw(FILE * out, const matrix_sparse * a)
{
  int i, j, m, n;
  
  m = a->rows;
  n = a->cols;
  for (i = 0; i < m; ++i)
  {
    for(j = 0; j < n - 1; ++ j)
      fprintf(out, "%g ", matrix_sparse_part(a, i, j));
    fprintf(out, "%g\n", matrix_sparse_part(a, i, j));
  }
}
