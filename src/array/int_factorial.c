#include "int.h"

int int_factorial(int n)
{
  int i, res;

  res = 1;
  for (i = 1; i <= n; ++i)
    res *= i;
  return res;
}
