#include <errno.h>
#include <stdlib.h>
#include "int.h"
#include "double.h"
#include "matrix_sparse.h"

matrix_sparse * matrix_sparse_identity(int n)
{
  matrix_sparse * a;

  a = (matrix_sparse *) malloc(sizeof(matrix_sparse));
  if (errno)
  {
    fputs("matrix_sparse_identity - cannot allocate memory for a\n", stderr);
    goto end;
  }

  a->rows = n;
  a->cols = n;

  a->cols_total = (int *) malloc(sizeof(int) * (n + 1));
  if (errno)
  {
    fputs("matrix_sparse_identity - cannot allocate memory for "
          "a->cols_total\n", stderr);
    goto a_free;
  }
  int_array_assign_identity(a->cols_total, n + 1);

  a->row_indices = (int *) malloc(sizeof(int) * n);
  if (errno)
  {
    fputs("matrix_sparse_identity - cannot allocate memory for "
          "a->row_indices\n", stderr);
    goto a_cols_total_free;
  }
  int_array_assign_identity(a->row_indices, n);

  a->values = (double *) malloc(sizeof(double) * n);
  if (errno)
  {
    fputs("matrix_sparse_identity - cannot allocate memory for "
          "a->row_indices\n", stderr);
    goto a_row_indices_free;
  }
  double_array_assign_constant(a->values, n, 1.);

  return a;

  /* cleaning if an error occurs */
a_row_indices_free:
  free(a->row_indices);
a_cols_total_free:
  free(a->cols_total);
a_free:
  free(a);
end:
  return NULL;
}
