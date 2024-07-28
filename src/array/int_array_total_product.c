#include "int.h"

int int_array_total_product(int n, const int * a)
{
  int i, result;

  result = 1;
  for (i = 0; i < n; ++i)
    result *= a[i];
  return result;
}
