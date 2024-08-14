#include "double.h"

void double_array_substitute(
  double * b, int n, const double * a, const int * position)
{
  int i;

  for (i = 0; i < n; ++i)
    b[i] = a[position[i]];
}
