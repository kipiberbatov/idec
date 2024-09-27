#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"
#include "double.h"
#include "matrix_sparse.h"

void matrix_sparse_mixed_linear_solve_with_diagonal_top_left_matrix(
  double * q,
  double * u,
  const double * a,
  const matrix_sparse * b,
  const double * g,
  const double * f)
{
  int b_nonzero_max, m, n;
  matrix_sparse b_times_inverse_a;
  matrix_sparse * b_transpose, * c;

  m = b->cols;
  n = b->rows;
  b_nonzero_max = b->cols_total[b->cols];

  fprintf(stderr, "\n%sa:%s\n", color_red, color_none);
  double_array_file_print(stderr, m, a, "--curly");
  fputc('\n', stderr);

  matrix_sparse_copy_topology(&b_times_inverse_a, b);
  b_times_inverse_a.values = (double *) malloc(sizeof(double) * b_nonzero_max);
  if (b_times_inverse_a.values == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot allocate memory for b_times_inverse_a.values\n", stderr);
    return;
  }
  memcpy(b_times_inverse_a.values, b->values, sizeof(double) * b_nonzero_max);
  matrix_sparse_multiply_with_inverse_of_diagonal(&b_times_inverse_a, a);
  fprintf(stderr, "\n%sb a^{-1}:%s\n", color_red, color_none);
  matrix_sparse_file_print(stderr, &b_times_inverse_a, "--matrix-form-curly");

  b_transpose = matrix_sparse_transpose(b);
  if (b_transpose == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate b_transpose = b^T\n", stderr);
    goto b_times_inverse_a_values_free;
  }
  fprintf(stderr, "\n%sb^T:%s\n", color_red, color_none);
  matrix_sparse_file_print(stderr, b_transpose, "--matrix-form-curly");

  c = matrix_sparse_product(&b_times_inverse_a, b_transpose);
  if (c == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate c = b a^{-1} b^T\n", stderr);
    goto b_transpose_free;
  }
  fprintf(stderr, "\n%sb a^{-1} b^T:%s\n", color_red, color_none);
  matrix_sparse_file_print(stderr, c, "--matrix-form-curly");

  double_array_negate(u, n, f);
  fprintf(stderr, "\n%s-f:%s\n", color_red, color_none);
  double_array_file_print(stderr, n, u, "--curly");
  fputc('\n', stderr);

  matrix_sparse_vector_multiply_add(u, &b_times_inverse_a, g);
  fprintf(stderr, "\n%sb a^{-1} g - f:%s\n", color_red, color_none);
  double_array_file_print(stderr, n, u, "--curly");
  fputc('\n', stderr);

  matrix_sparse_linear_solve(c, u, "--lu");
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate variable u\n", stderr);
    goto c_free;
  }
  fprintf(stderr, "\n%su:%s\n", color_red, color_none);
  double_array_file_print(stderr, n, u, "--curly");
  fputc('\n', stderr);

  memcpy(q, g, sizeof(double) * m);
  matrix_sparse_vector_subtract_product(q, b_transpose, u);
  double_array_pointwise_divide(q, m, a);

c_free:
  matrix_sparse_free(c);
b_transpose_free:
  matrix_sparse_free(b_transpose);
b_times_inverse_a_values_free:
  free(b_times_inverse_a.values);
}
