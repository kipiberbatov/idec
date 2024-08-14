#include <errno.h>
#include "matrix_sparse_private.h"

void matrix_sparse_file_print_mathematica_sparse(
  FILE * out, const matrix_sparse * a)
{
  int i, i_loc, j, m, n;
  int * a_cols_total, * a_row_indices;
  double x;
  double * a_values;

  m = a->rows;
  n = a->cols;
  a_cols_total = a->cols_total;
  a_row_indices = a->row_indices;
  a_values = a->values;

  fputs("SparseArray[{", out);
  for (j = 0; j < n; ++j)
  {
    for (i_loc = a_cols_total[j]; i_loc < a_cols_total[j + 1]; ++i_loc)
    {
      i = a_row_indices[i_loc];
      x = a_values[i_loc];
      fprintf(out, "{%d,%d}->%g", i + 1, j + 1, x);
      if (i_loc < a_cols_total[n] - 1)
        fputc(',', out);
    }
  }
  fprintf(out, "},{%d,%d}]\n", m, n);
}
