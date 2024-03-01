#include "int.h"

void int_array_assign_identity(int * a, int n)
{
  int i;
  
  for (i = 0; i < n; ++i)
    a[i] = i;
}

void int_array_assign_constant(int * a, int n, int c)
{
  int i;
  
  for (i = 0; i < n; ++i)
    a[i] = c;
}

void int_array_substitute(int * b, int n, const int * a, const int * position)
{
  int i;
  
  for (i = 0; i < n; ++i)
    b[i] = a[position[i]];
}

void int_array_substitute_inverse(
  int * b, int n, const int * a, const int * position)
{
  int i;
  
  for (i = 0; i < n; ++i)
    b[position[i]] = a[i];
}

void int_array_sum(int * c, int n, const int * a, const int * b)
{
  int i;
  
  for (i = 0; i < n; ++i)
    c[i] = a[i] + b[i];
}

void int_array_set_difference(
  int * b_bar, int p, const int * a, int q, const int * b)
{
  int i, ind;
  
  ind = 0;
  for (i = 0; i < p; ++i)
    if (!int_array_member(q, b, a[i]))
    {
      b_bar[ind] = a[i];
      ++ind;
    }
}

int int_array_total_sum(int n, const int * a)
{
  int i, result;
  
  result = 0;
  for (i = 0; i < n; ++i)
    result += a[i];
  return result;
}

int int_array_total_product(int n, const int * a)
{
  int i, result;
  
  result = 1;
  for (i = 0; i < n; ++i)
    result *= a[i];
  return result;
}

int int_array_member(int n, const int * a, int element)
{
  int i;
  
  for (i = 0; i < n; ++i)
    if (element == a[i])
      return 1;
  return 0;
}

int int_array_flatten_index(int d, const int * dimensions, const int * indices)
{
  int flattened_index, prod, r;
  
  flattened_index = 0;
  for (r = 0; r < d; ++r)
  {
    prod = int_array_total_product(d - (r + 1), dimensions + r + 1);
    flattened_index += prod * indices[r];
  }
  return flattened_index;
}

int int_array_positive(int n, const int * a)
{
  int i;
  
  /* check for at least one negative number */
  for (i = 0; i < n; ++i)
    if (a[i] < 0)
      return 0;
  
  /* check for at least one positive number if there are no negative numbers */
  for (i = 0; i < n; ++i)
    if (a[i] > 0)
      return 1;
  
  /* a is not positive if all elements are zeroes */
  return 0;
}

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

int int_array_combination_index(int * comb, int m, int n)
{
  int i, j, prev, res, a0;
  
  if (n != 0)
  {
    a0 = comb[0];
    prev = 0;
    for (i = 1; i <= a0; ++i)
      prev += int_binomial(m - i, n - 1);
    ++a0;
    for (j = 1; j < n; ++j)
      comb[j] -= a0;
    ++comb;
    res = prev + int_array_combination_index(comb, m - a0, n - 1);
  }
  else
    res = 0;
  return res;
}
