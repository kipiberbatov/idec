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
  a q + b u = g,
  b^T q = f.
$$

********************************** definition **********************************
We can solve the system directly, without much overhead, thanks to the fact that
$a^{-1}$ is also diagonal.
Indeed,
$q = a^{-1} (g - b u)$
and therefore
$f = b^T q = b^T (a^{-1} (g - b u)) = b^T a^{-1} g - b^T a^{-1} b u$
from which we gen the following linear system with respect to $u$:
$b^T a^{-1} b u = b^T a^{-1} g - f$.
It is assumed that the symmetric matrix $c := b^T a^{-1} b$ is invertible.
Hence, we have the following solving procedure:
$$
  u := matrix_sparse_linear_solve_cholesky(b^T a^{-1} b, b^T a^{-1} g - f),
  q := a^{-1} (g - b u).
$$
*/
void matrix_sparse_mixed_solve_with_diagonal_square_matrix(
  double * q,
  double * u,
  const double * a,
  const matrix_sparse * b,
  const double * g,
  const double * f)
{
  int m, n;
  double * a_inverse; /* diagonal matrix */
  double * rhs_u;
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

  rhs_u = calloc(n, sizeof(double));
  if (lhs == NULL)
  {
    fprintf(stderr,
      "%s:%d: cannot allocate memory for rhs_y", __FILE__, __LINE__);
    goto lhs_free;
  }

  matrix_sparse_multiply_with_vector_and_add_to(rhs_u, c, g);
  double_array_subtract_from(rhs_u, n, f);
  matrix_sparse_linear_solve(u, lhs, rhs_u, "--cholesky");
  if (errno)
  {
    fprintf(stderr,
      "%s:%d: cannot solve linear system for y", __FILE__, __LINE__);
    goto rhs_y_free;
  }

  double_array_copy(q, m, g);
  matrix_sparse_multiply_with_vector_and_subtract_from(q, b, u);
  double_array_left_multiply_with_inverse_of_diagonal_matrix(q, m, a);

rhs_u_free:
  free(rhs_u);
lhs_free:
  matrix_sparse_free(lhs);
c_free:
  matrix_sparse_free(c);
end:
  return;
}
