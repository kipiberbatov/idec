#include "matrix.h"

void matrix_times_transpose(double * b, int d, int n, const double * a)
{
  int p, i, q;
  double a_q_i;
  const double * a_i;
  double * b_q;
  
  for (i = 0; i < n; ++i)
  {
    a_i = a + d * i;
    for (q = 0; q < d; ++q)
    {
      b_q = b + d * q;
      a_q_i = a_i[q];
      for (p = 0; p < d; ++p)
      {
        b_q[p] += a_q_i * a_i[p];
      }
    }
  }
}
