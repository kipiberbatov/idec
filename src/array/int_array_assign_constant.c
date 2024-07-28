#include "int.h"

void int_array_assign_constant(int * a, int n, int c)
{
  int i;

  for (i = 0; i < n; ++i)
    a[i] = c;
}
