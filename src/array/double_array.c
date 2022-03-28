#include <math.h>
#include "double.h"

void double_array_assign_identity(double * a, int n)
{
  int i;
  
  for (i = 0; i < n; ++i)
    a[i] = i;
}

void double_array_assign_constant(double * a, int n, double c)
{
  int i;
  
  for (i = 0; i < n; ++i)
    a[i] = c;
}

void double_array_substitute(
  double * b, int n, const double * a, const int * position)
{
  int i;
  
  for (i = 0; i < n; ++i)
    b[i] = a[position[i]];
}

void double_array_substitute_inverse(
  double * b, int n, const double * a, const int * position)
{
  int i;
  
  for (i = 0; i < n; ++i)
    b[position[i]] = a[i];
}

void double_array_add_to(double * a, int d, const double * b)
{
  int i;
  
  for (i = 0; i < d; ++i)
    a[i] += b[i];
}

void double_array_multiply_with(double * a, int d, double lambda)
{
  int i;
  
  for (i = 0; i < d; ++i)
    a[i] *= lambda;
}

double double_array_dot_product(int d, const double * a, const double * b)
{
  int i;
  double res;
  
  res = 0;
  for (i = 0; i < d; ++i)
    res += a[i] * b[i];
  return res;
}

double double_array_norm(int d, const double * a)
{
  double length_square;
  
  length_square = double_array_dot_product(d, a, a);
  return sqrt(length_square);
}

void double_array_normalise(double * res, int d, const double * a)
{
  int i;
  double l;
  
  l = double_array_norm(d, a);
  for (i = 0; i < d; ++i)
    res[i] = a[i] / l;
}

void double_array_difference(
  double * res, int d, const double * a, const double * b)
{
  int i;
  
  for (i = 0; i < d; ++i)
    res[i] = a[i] - b[i];
}
