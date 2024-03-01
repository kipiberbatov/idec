#include "double_array_difference.h"

/* c := a - b (all three are arrays of length n). */
void double_array_difference(
  double * c,
  int n,
  const double * a,
  const double * b)
{
  int i;
  
  for (i = 0; i < n; ++i)
    res[i] = a[i] - b[i];
}
