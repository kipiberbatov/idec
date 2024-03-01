#include "double_array_multiply_with.h"

/* Sets a *= lambda. */
void double_array_multiply_with(double * a, int n, double lambda)
{
  int i;
  
  for (i = 0; i < n; ++i)
    a[i] *= lambda;
}
