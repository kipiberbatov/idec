#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "matrix_sparse.h"

void matrix_sparse_mixed_linear_solve_with_diagonal_top_left_matrix(
  double * q,
  double * u,
  const double * a,
  const matrix_sparse * b,
  const double * g,
  const double * f)
{
  int i, m, n;
  matrix_sparse * c, * d;

  m = b->cols;
  n = b->rows;

  c = matrix_sparse_transpose(b);
  if (c == NULL)
  {
    fprintf(stderr, "%s:%d: cannot calculate c\n", __FILE__, __LINE__);
    return;
  }

  matrix_sparse_multiply_with_inverse_of_diagonal(c, a);
  d = matrix_sparse_product(c, b);
  if (d == NULL)
  {
    fprintf(stderr, "%s:%d: cannot calculate d\n", __FILE__, __LINE__);
    goto c_free;
  }

  for (i = 0; i < n; ++i)
    u[i] = -f[i];
  matrix_sparse_vector_multiply_add(u, c, g);
  matrix_sparse_linear_solve(d, u, "--cholesky");
  if (errno)
  {
    fprintf(stderr, "%s:%d: cannot solve for u\n", __FILE__, __LINE__);
    goto d_free;
  }

  memcpy(q, g, sizeof(double) * m);
  matrix_sparse_vector_subtract_product(q, b, u);

d_free:
  matrix_sparse_free(d);
c_free:
  matrix_sparse_free(c);
}
