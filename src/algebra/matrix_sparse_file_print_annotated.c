#include <errno.h>
#include "matrix_sparse_private.h"

void matrix_sparse_file_print_annotated(FILE * out, const matrix_sparse * a)
{
  int ind, j, m, n;
  int * a_cols_total, * a_row_indices;
  double * a_values;
  
  m = a->rows;
  n = a->cols;
  a_cols_total = a->cols_total;
  a_row_indices = a->row_indices;
  a_values = a->values;
  fprintf(out, "%d-by-%d sparse matrix, maximal number of nonzero values: %d\n",
          m, n, a_cols_total[n]);
  for (j = 0; j < n; ++j)
  {
    fprintf(out, "  column %d : locations %d to %d\n",
            j, a_cols_total[j], a_cols_total[j + 1] - 1);
    for (ind = a_cols_total[j]; ind < a_cols_total[j + 1]; ++ind)
      fprintf(out, "    %d : %g\n", a_row_indices[ind], a_values[ind]);
  }
}
