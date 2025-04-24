#include "double_array.h"

void double_array_assign_identity(double * a, int n)
{
  int i;

  for (i = 0; i < n; ++i)
    a[i] = i;
}
