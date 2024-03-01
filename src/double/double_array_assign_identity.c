#include "double_array_assign_identity.h"

/* Sets a := {0, 1, ..., n - 1}. */
void double_array_assign_identity(double * a, int n)
{
  int i;
  
  for (i = 0; i < n; ++i)
    a[i] = i;
}
