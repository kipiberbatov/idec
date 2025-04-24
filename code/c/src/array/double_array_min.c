#include "double_array.h"

double double_array_min(int n, const double * a)
{
  int i;
  double min;

  min = a[0];
  for (i = 1; i < n; ++i)
    if (a[i] < min)
      min = a[i];
  return min;
}
