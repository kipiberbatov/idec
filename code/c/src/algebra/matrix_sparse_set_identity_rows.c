#include "matrix_sparse.h"
void matrix_sparse_set_identity_rows(
  matrix_sparse * lhs,
  const jagged1 * boundary_positions)
{
  int column_j_nonzero_total, i, i_local, j;
  int * column_j_row_indices;
  double * column_j_values;

  for (j = 0; j < lhs->cols; ++j)
  {
    column_j_nonzero_total = lhs->cols_total[j + 1] - lhs->cols_total[j];
    column_j_row_indices = lhs->row_indices + lhs->cols_total[j];
    column_j_values = lhs->values + lhs->cols_total[j];
    for (i_local = 0; i_local < column_j_nonzero_total; ++i_local)
    {
      i = column_j_row_indices[i_local];
      if (jagged1_member(boundary_positions, i))
      {
        if (i == j)
          column_j_values[i_local] = 1.;
        else
          column_j_values[i_local] = 0.;
      }
    }
  }
}
