#include <math.h>

#include "double.h"

double double_array_absolute_max(int n, const double * a)
{
  int i;
  double max;

  max = fabs(a[0]);
  for (i = 1; i < n; ++i)
    if (max < fabs(a[i]))
      max = fabs(a[i]);
  return max;
}
