#include "int.h"

void int_array_4_values_get(
  const int * a, int * x0, int * x1, int * x2, int * x3)
{
  *x0 = a[0];
  *x1 = a[1];
  *x2 = a[2];
  *x3 = a[3];
}

void int_array_4_values_set(int * a, int x0, int x1, int x2, int x3)
{
  a[0] = x0;
  a[1] = x1;
  a[2] = x2;
  a[3] = x3;
}
