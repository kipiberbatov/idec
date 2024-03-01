#include "double_array_dot_product.h"

/* Finds a . b := a[0] * b[0] + ... + a[n - 1] * b[n - 1]. */
double double_array_dot_product(int n, const double * a, const double * b);
{
  int i;
  double res;
  
  res = 0;
  for (i = 0; i < n; ++i)
    res += a[i] * b[i];
  return res;
}
