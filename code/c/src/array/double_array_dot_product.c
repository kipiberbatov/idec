#include "double_array.h"

double double_array_dot_product(int d, const double * a, const double * b)
{
  int i;
  double res;

  res = 0;
  for (i = 0; i < d; ++i)
    res += a[i] * b[i];
  return res;
}
