#include "int.h"

void int_array_combination_next(int * a, int m, int n)
{
  int i, j;

  if (a[n - 1] != m - 1)
    ++a[n - 1];
  else
  {
    i = n - 2;
    while (a[i + 1] == a[i] + 1)
      --i;
    ++a[i];
    for (j = i + 1; j < n; ++j)
      a[j] = a[j - 1] + 1;
  }
}
