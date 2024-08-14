#include "int.h"

void int_array_cartesian_product_next(int * a, int d, const int * n)
{
  int i, j;

  i = d - 1;
  while (a[i] == (n[i] - 1))
    --i;
  ++a[i];
  for (j = i + 1; j < d; ++j)
    a[j] = 0;
}
