#include <math.h>

#include "double.h"

double double_array_absolute_min(int n, const double * a)
{
  int i;
  double min;

  min = fabs(a[0]);
  for (i = 1; i < n; ++i)
    if (min > fabs(a[i]))
      min = fabs(a[i]);
  return min;
}
