#include "double.h"

void double_array_add_to(double * a, int d, const double * b)
{
  int i;

  for (i = 0; i < d; ++i)
    a[i] += b[i];
}
