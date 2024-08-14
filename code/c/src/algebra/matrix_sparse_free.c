#include <stdlib.h>
#include "matrix_sparse.h"

void matrix_sparse_free(matrix_sparse * a)
{
  free(a->values);
  free(a->row_indices);
  free(a->cols_total);
  free(a);
}

void matrix_sparse_free_shared(matrix_sparse * a)
{
  free(a->values);
  free(a);
}
