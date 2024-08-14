#include "double.h"

void double_array_difference(
  double * res, int d, const double * a, const double * b)
{
  int i;

  for (i = 0; i < d; ++i)
    res[i] = a[i] - b[i];
}
