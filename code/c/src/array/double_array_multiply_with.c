#include "double.h"

void double_array_multiply_with(double * a, int d, double lambda)
{
  int i;

  for (i = 0; i < d; ++i)
    a[i] *= lambda;
}
