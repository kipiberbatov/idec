#include "int.h"

void int_array_substitute(int * b, int n, const int * a, const int * position)
{
  int i;

  for (i = 0; i < n; ++i)
    b[i] = a[position[i]];
}
