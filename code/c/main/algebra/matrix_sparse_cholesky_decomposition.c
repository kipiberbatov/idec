#include "matrix_sparse.h"

int main(void)
{
#define N 4
  int a_rows = N;
  int a_columns = N;
  int a_cols_total[N + 1] = {0, 2, 5, 8, 10};
  int a_row_indices[10] = {0, 1, 0, 1, 2, 1, 2, 3, 2, 3};
  double a_values[10] = {2, -1, -1, 2, -1, -1, 2, -1, -1, 2};
  matrix_sparse a = {a_rows, a_columns, a_cols_total, a_row_indices, a_values};
  matrix_sparse * l, * l_transpose, * l_times_l_transpose;
  puts("# a:");
  matrix_sparse_file_print(stdout, &a, "--matrix-form-raw");

  l = matrix_sparse_cholesky_decomposition(&a);
  puts("\n# l:");
  matrix_sparse_file_print(stdout, l, "--matrix-form-raw");

  l_transpose = matrix_sparse_transpose(l);
  puts("\n# l^T:");
  matrix_sparse_file_print(stdout, l_transpose, "--matrix-form-raw");

  l_times_l_transpose = matrix_sparse_product(l, l_transpose);
  puts("\n# l l^T:");
  matrix_sparse_file_print(stdout, l_times_l_transpose, "--matrix-form-raw");

  matrix_sparse_free(l_times_l_transpose);
  matrix_sparse_free(l_transpose);
  matrix_sparse_free(l);
  return 0;


}
