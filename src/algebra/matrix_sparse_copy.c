#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "matrix_sparse.h"

matrix_sparse * matrix_sparse_copy(const matrix_sparse * a)
{
  int nonzero_max;
  matrix_sparse * b;

  b = (matrix_sparse *) malloc(sizeof(matrix_sparse));
  if (errno)
  {
  	fputs("Cannot allocate memory for matrix copy b\n", stderr);
  	goto end;
  }

  b->rows = a->rows;
  b->cols = a->cols;
  
  b->cols_total = (int *) malloc(sizeof(int) * (b->cols + 1));
  if (errno)
  {
  	fputs("Cannot allocate memory for b->cols_total\n", stderr);
  	goto b_free;
  }
  memcpy(b->cols_total, a->cols_total, sizeof(int) * (b->cols + 1));
  
  nonzero_max = b->cols_total[b->cols];
  
  b->row_indices = (int *) malloc(sizeof(int) * nonzero_max);
  if (errno)
  {
  	fputs("Cannot allocate memory for b->row_indices\n", stderr);
  	goto b_cols_total_free;
  }
  memcpy(b->row_indices, a->row_indices, sizeof(int) * nonzero_max);

  b->values = (double *) malloc(sizeof(double) * nonzero_max);
  if (errno)
  {
  	fputs("Cannot allocate memory for b->rvalues\n", stderr);
  	goto b_row_indices_free;
  }
  memcpy(b->values, a->values, sizeof(double) * nonzero_max);

  return b;

  /* cleaning if an error occurs */
b_row_indices_free:
  free(b->row_indices);
b_cols_total_free:
  free(b->cols_total);
b_free:
  free(b);
end:
  return NULL;
}
