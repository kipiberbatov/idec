#include "int.h"

int int_array_total_sum(int n, const int * a)
{
  int i, result;
  
  result = 0;
  for (i = 0; i < n; ++i)
    result += a[i];
  return result;
}
