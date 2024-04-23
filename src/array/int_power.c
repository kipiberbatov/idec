#include "int.h"

int int_power(int a, int n)
{
  int i, res;

  res = 1;
  for (i = 0; i < n; ++ i)
    res *= a;
  return res;
}
