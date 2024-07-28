#include "int.h"

void int_array_assign_identity(int * a, int n)
{
  int i;

  for (i = 0; i < n; ++i)
    a[i] = i;
}
