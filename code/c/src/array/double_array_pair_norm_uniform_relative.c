#include <math.h>

#include "double_array.h"

double double_array_pair_norm_uniform_relative(
  int n, const double * a, const double * b)
{
  int i;
  double c_norm, tmp;

  c_norm = 0;
  for (i = 0; i < n; ++i)
  {
    tmp = fabs(a[i] - b[i]);
    if (tmp > c_norm)
      c_norm = tmp;
  }
  return c_norm / double_array_norm_uniform(n, a);
}
