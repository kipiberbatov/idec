#include "matrix_sparse.h"

void matrix_sparse_copy_topology(matrix_sparse * b, const matrix_sparse * a)
{
  b->rows = a->rows;
  b->cols = a->cols;
  b->cols_total = a->cols_total;
  b->row_indices = a->row_indices;
}
