#include "double.h"

void double_array_normalize(double * res, int d, const double * a)
{
  int i;
  double l;
  
  l = double_array_norm(d, a);
  for (i = 0; i < d; ++i)
    res[i] = a[i] / l;
}
