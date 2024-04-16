#include <math.h>

#include "double.h"

double double_array_norm_uniform(int n, const double * a)
{
  int i;
  double b, result;
  result = 0;
  for (i = 0; i < n; ++i)
  {
    b = fabs(a[i]);
    if (b > result)
      result = b;
  }
  return result;
}
