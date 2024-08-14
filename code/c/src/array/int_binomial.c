#include "int.h"

int int_binomial(int n, int k)
{
  int i, k1, res;

  k1 = (n >= 2 * k ? k : n - k);
  res = 1;
  for (i = 1; i <= k1; ++i)
    res = (res * (n - i + 1)) / i;
  return res;
}
