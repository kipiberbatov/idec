#include "matrix_sparse.h"

double * matrix_sparse_part_pointer(const matrix_sparse * a, int i, int j)
{
  int i_loc;
  int * a_cols_total, * a_row_indices;
  double * a_values;

  a_cols_total = a->cols_total;
  a_row_indices = a->row_indices;
  a_values = a->values;
  for (i_loc = a_cols_total[j]; i_loc < a_cols_total[j + 1]; ++i_loc)
    if (a_row_indices[i_loc] == i)
      return a_values + i_loc;
  return NULL;
}
