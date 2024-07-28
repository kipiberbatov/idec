#include "matrix.h"

/*
Let $a be an $n * $d matrix.
Let $x be a $d vector.
We calculate the $n vector $b = product($a, $x).
$b is initially set to zero.
*/
void matrix_times_vector(
  double * b, int n, int d, const double * a, const double * x)
{
  int p, i;
  double x_p;
  const double * a_p;

  for (p = 0; p < d; ++p)
  {
    a_p = a + n * p;
    x_p = x[p];
    for (i = 0; i < n; ++i)
    {
      b[i] += a_p[i] * x_p;
    }
  }
}
