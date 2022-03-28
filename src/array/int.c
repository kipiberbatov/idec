#include "int.h"

void int_swap(int * a, int * b)
{
  int tmp;
  
  tmp = *a;
  *a = *b;
  *b = tmp;
}

int int_power(int a, int n)
{
  int i, res;

  res = 1;
  for (i = 0; i < n; ++ i)
    res *= a;
  return res;
}

int int_binomial(int n, int k)
{
  int i, k1, res;
  
  k1 = (n >= 2 * k ? k : n - k);
  res = 1;
  for (i = 1; i <= k1; ++i)
    res = (res * (n - i + 1)) / i;
  return res;
}

int int_factorial(int n)
{
  int i, res;
  
  res = 1;
  for (i = 1; i <= n; ++i)
    res *= i;
  return res;
}
