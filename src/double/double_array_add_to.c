#include "double_array_add_to.h"

/* Sets a += b (both are arrays of length n). */
void double_array_add_to(double * a, int n, const double * b)
{
  int i;
  
  for (i = 0; i < n; ++i)
    a[i] += b[i];
}
