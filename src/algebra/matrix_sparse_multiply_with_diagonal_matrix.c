#include "matrix_sparse.h"

/* Find the a . diagonal(d[0], ..., d[a->cols - 1]) . */
void matrix_sparse_multiply_with_diagonal_matrix(matrix_sparse * a, double * d)
{
  int i_loc, index, j, n;
  int * a_cols_total, * a_row_indices;
  double * a_values;

  n = a->cols;
  a_cols_total = a->cols_total;
  a_row_indices = a->row_indices;
  a_values = a->values;

  for (j = 0; j < n; ++j)
  {
  	index = a_cols_total[j];
  	for (i_loc = 0; i_loc < a_cols_total[j + 1] - a_cols_total[j]; ++i_loc)
  		a_values[index + i_loc] *= d[j];
  }
}
