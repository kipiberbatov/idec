#include "double.h"

void double_array_pointwise_multiply(double * b, int n, const double * a)
{
  int i;

  for (i = 0; i < n; ++i)
    b[i] *= a[i];
}