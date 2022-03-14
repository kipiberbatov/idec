#include "int.h"

void int_array_assign_identity(int * a, int n)
{
  int i;
  
  for (i = 0; i < n; ++i)
    a[i] = i;
}

void int_array_assign_integer(int * a, int n, int c)
{
  int i;
  
  for (i = 0; i < n; ++i)
    a[i] = c;
}

void int_array_substitute(int * b, int n, const int * a, const int * k)
{
  int i;
  
  for (i = 0; i < n; ++i)
    b[i] = a[k[i]];
}

void int_array_substitute_inverse(
  int * z, int p_minus_q, const int * b_bar, const int * w)
{
  int i;
  
  for (i = 0; i < p_minus_q; ++i)
    z[b_bar[i]] = w[i];
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

int int_array_total_product(const int * a, int begin, int end)
{
  int i, result;
  
  result = 1;
  for (i = begin; i < end; ++i)
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
    prod = int_array_total_product(dimensions, r + 1, d);
    flattened_index += prod * indices[r];
  }
  return flattened_index;
}
