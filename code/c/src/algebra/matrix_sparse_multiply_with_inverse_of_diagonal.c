#include "matrix_sparse.h"

void matrix_sparse_multiply_with_inverse_of_diagonal(
  matrix_sparse * b,
  const double * a)
{
  int b_cols, b_rows_j, i_local, j;
  int * b_cols_total;
  double a_j;
  double * b_values, * b_values_j;

  b_cols = b->cols;
  b_cols_total = b->cols_total;
  b_values = b->values;
  for (j = 0; j < b_cols; ++j)
  {
    b_rows_j = b_cols_total[j + 1] - b_cols_total[j];
    b_values_j = b_values + b_cols_total[j];
    a_j = a[j];
    for (i_local = 0; i_local < b_rows_j; ++i_local)
      b_values_j[i_local] /= a_j;
  }
}
