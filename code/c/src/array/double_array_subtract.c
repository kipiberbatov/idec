#include "double.h"

void double_array_subtract(double * a, int n, const double * b)
{
  int i;
  for (i = 0; i < n; ++i)
    a[i] -= b[i];
}
