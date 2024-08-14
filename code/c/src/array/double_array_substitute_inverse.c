#include "double.h"

void double_array_substitute_inverse(
  double * b, int n, const double * a, const int * position)
{
  int i;

  for (i = 0; i < n; ++i)
    b[position[i]] = a[i];
}
