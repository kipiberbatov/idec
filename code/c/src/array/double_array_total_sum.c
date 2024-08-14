#include "double.h"

double double_array_total_sum(int n, const double * a)
{
  int i;
  double result;

  result = 0;
  for (i = 0; i < n; ++i)
    result += a[i];
  return result;
}
