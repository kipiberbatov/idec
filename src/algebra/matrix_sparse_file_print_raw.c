#include <errno.h>
#include "double.h"
#include "int.h"
#include "matrix_sparse_private.h"

void matrix_sparse_file_print_raw(FILE * out, const matrix_sparse * a)
{
  int n, nonzero_max;
  
  n = a->cols;
  nonzero_max = a->cols_total[n];
  fprintf(out, "%d\n", a->rows);
  fprintf(out, "%d\n", n);
  int_array_file_print(out, (n + 1), a->cols_total, "--raw");
  int_array_file_print(out, nonzero_max, a->row_indices, "--raw");
  double_array_file_print(out, nonzero_max, a->values, "--raw");
}
