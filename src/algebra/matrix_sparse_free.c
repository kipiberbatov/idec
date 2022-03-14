#include <stdlib.h>
#include "matrix_sparse.h"

void matrix_sparse_free(matrix_sparse * a)
{
  free(a->values);
  free(a->row_indices);
  free(a->cols_total);
  free(a);
}

void matrix_sparse_free_array(matrix_sparse ** a, int n)
{
  int i;
  
  for (i = n - 1; i >= 0; --i)
    matrix_sparse_free(a[i]);
  free(a);
}

void matrix_sparse_free_shared(matrix_sparse * a)
{
  free(a->values);
  free(a);
}

void matrix_sparse_free_shared_array(matrix_sparse ** a, int n)
{
  int i;
  
  for (i = n - 1; i >= 0; --i)
    matrix_sparse_free_shared(a[i]);
  free(a);
}
