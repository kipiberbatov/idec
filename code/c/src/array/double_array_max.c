#include "double.h"

double double_array_max(int n, const double * a)
{
  int i;
  double max;

  max = a[0];
  for (i = 1; i < n; ++i)
    if (a[i] > max)
      max = a[i];
  return max;
}
