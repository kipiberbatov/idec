#include "imath.h"

void imath_swap(int * a, int * b)
{
  int tmp;
  
  tmp = *a;
  *a = *b;
  *b = tmp;
}

int imath_pow(int a, int b)
{
  int i, res;

  res = 1;
  for (i = 0; i < b; ++ i)
    res *= a;
  return res;
}

void imath_cartesian_product_next(int * a, int d, const int * n)
{
  int i, j;
  
  i = d - 1;
  while (a[i] == (n[i] - 1))
    --i;
  ++a[i];
  for (j = i + 1; j < d; ++j)
    a[j] = 0;
}

int imath_binom(int a, int b)
{
  int i, res;
  
  res = 1;
  for (i = 1; i <= b; ++i)
    res = (res * (a - i + 1)) / i;
  return res;
}

void imath_combination_next(int * a, int m, int n)
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

int imath_combination_index(int * comb, int m, int n)
{
  int i, j, prev, res, a0;
  
  if (n != 0)
  {
    a0 = comb[0];
    prev = 0;
    for (i = 1; i <= a0; ++i)
      prev += imath_binom(m - i, n - 1);
    ++a0;
    for (j = 1; j < n; ++j)
      comb[j] -= a0;
    ++comb;
    res = prev + imath_combination_index(comb, m - a0, n - 1);
  }
  else
    res = 0;
  return res;
}

int imath_factorial(int n)
{
  int i, res;
  
  res = 1;
  for (i = 1; i <= n; ++i)
    res *= i;
  return res;
}
