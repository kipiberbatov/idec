#include <string.h>

#include "matrix.h"

void matrix_moore_penrose_inverse(double * b, int d, int n, const double * a)
{
  enum {max_dim = 3};
  int p, q, i;
  double a_q_i;
  const double * a_i;
  double * tmp1_q;
  double tmp[max_dim * max_dim] = {0}, tmp1[max_dim * max_dim];

  memset(b, 0, sizeof(double) * d * n);
  matrix_times_transpose(tmp, d, n, a);
  matrix_inverse(tmp1, d, tmp);
  for (i = 0; i < n; ++i)
  {
    a_i = a + d * i;
    for (q = 0; q < d; ++q)
    {
      a_q_i = a_i[q];
      tmp1_q = tmp1 + d * q;
      for (p = 0; p < d; ++p)
      {
        b[i + p * n] += a_q_i * tmp1_q[p];
      }
    }
  }
}
