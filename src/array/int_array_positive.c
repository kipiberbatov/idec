#include "int.h"

int int_array_positive(int n, const int * a)
{
  int i;
  
  /* check for at least one negative number */
  for (i = 0; i < n; ++i)
    if (a[i] < 0)
      return 0;
  
  /* check for at least one positive number if there are no negative numbers */
  for (i = 0; i < n; ++i)
    if (a[i] > 0)
      return 1;
  
  /* a is not positive if all elements are zeroes */
  return 0;
}
