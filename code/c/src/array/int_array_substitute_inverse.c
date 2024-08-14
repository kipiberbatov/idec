#include "int.h"

void int_array_substitute_inverse(
  int * b, int n, const int * a, const int * position)
{
  int i;

  for (i = 0; i < n; ++i)
    b[position[i]] = a[i];
}
