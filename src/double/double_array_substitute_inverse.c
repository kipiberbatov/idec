#include "double_array_substitute_inverse.h"

/* Sets b[position[0]] := a[0], ..., b[position[n - 1]] := a[n - 1] . */
void double_array_substitute_inverse(
  double * b,
  int n,
  const double * a,
  const int * position)
{
  int i;
  
  for (i = 0; i < n; ++i)
    b[position[i]] = a[i];
}
