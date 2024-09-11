#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "double.h"
#include "matrix_sparse.h"

/*
********************************* declaration **********************************
Let:
  . $m$ and $n$ be positive integers;
  . $a$ be an invertible $m * m$ diagonal matrix (stored as a pointer to the
    area of memory occupied with its diagonal elements);
  . $b$ be an $m * n$ sparse matrix ($b$ be a pointer to matrix_sparse,
    $m$ and $n$ are stored in $b$);
  . $f$ and $g$ be real vectors of lengths $m$ and $n$ respectively (stored as
    pointers to memory segments occupied with their values of type double).

We are looking for $x$ and $y$ -- pointers to already allocated memory segments
of lengths $m$ and $n$ respectively -- that satisfy the following linear system:
$$
  a x + b y = f,
  b^T x = g.
$$

********************************** definition **********************************
We can solve the system directly, without much overhead, thanks to the fact that
$a^{-1}$ is also diagonal.
Indeed,
$x = a^{-1} (f - b y)$
and therefore
$g = b^T x = b^T (a^{-1} (f - b y)) = b^T a^{-1} f - b^T a^{-1} b y$
from which we gen the following linear system with respect to $y$:
$b^T a^{-1} b y = b^T a^{-1} f - g$.
It is assumed that the symmetric matrix $c := b^T a^{-1} b$ is invertible.
Hence, we have the following solving procedure:
$$
  y := matrix_sparse_linear_solve_cholesky(b^T a^{-1} b, b^T a^{-1} f - g),
  x := a^{-1} (f - b y).
$$
*/
void matrix_sparse_mixed_solve_with_diagonal_square_matrix(
  double * x,
  double * y,
  const double * a,
  const matrix_sparse * b,
  const double * f,
  const double * g)
{
  int m, n;
  double * a_inverse; /* diagonal matrix */
  double * rhs_x, * rhs_y;
  matrix_sparse * c, * lhs;

  m = b->rows;
  n = b->cols;

  c = matrix_sparse_transpose(b);
  if (c == NULL)
  {
    fprintf(stderr,
      "%s:%d: cannot calculate transpose of b", __FILE__, __LINE__);
    goto end;
  }
  matrix_sparse_right_multiply_with_inverse_of_diagonal_matrix(c, a);

  lhs = matrix_sparse_multiply(c, b);
  if (lhs == NULL)
  {
    fprintf(stderr, "%s:%d: cannot calculate lhs", __FILE__, __LINE__);
    goto c_free;
  }

  rhs_y = calloc(n, sizeof(double));
  if (lhs == NULL)
  {
    fprintf(stderr,
      "%s:%d: cannot allocate memory for rhs_y", __FILE__, __LINE__);
    goto lhs_free;
  }

  matrix_sparse_multiply_with_vector_and_add_to(rhs_y, c, f);
  double_array_subtract_from(rhs_y, n, g);
  matrix_sparse_linear_solve(y, lhs, rhs_y, "--cholesky");
  if (errno)
  {
    fprintf(stderr,
      "%s:%d: cannot solve linear system for y", __FILE__, __LINE__);
    goto rhs_y_free;
  }

  double_array_copy(x, m, f);
  matrix_sparse_multiply_with_vector_and_subtract_from(x, b, y);
  double_array_left_multiply_with_inverse_of_diagonal_matrix(x, m, a);

rhs_y_free:
  free(rhs_y);
lhs_free:
  matrix_sparse_free(lhs);
c_free:
  matrix_sparse_free(c);
end:
  return;
}
