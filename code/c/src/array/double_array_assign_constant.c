#include "double_array.h"

void double_array_assign_constant(double * a, int n, double c)
{
  int i;

  for (i = 0; i < n; ++i)
    a[i] = c;
}
