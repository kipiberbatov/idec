#include "double_array_assign_constant.h"

/* Sets a := {c, c, ..., c} (n times). */
void double_array_assign_constant(double * a, int n, double c)
{
  int i;
  
  for (i = 0; i < n; ++i)
    a[i] = c;
}
