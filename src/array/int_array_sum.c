#include "int.h"

void int_array_sum(int * c, int n, const int * a, const int * b)
{
  int i;
  
  for (i = 0; i < n; ++i)
    c[i] = a[i] + b[i];
}
