#include <stdlib.h>

#include "double_array2_free.h"

/* Free an array arr of length n of arrays of doubles. */
void double_array2_free(double ** arr, int n)
{
  int p;
  
  for (p = n - 1; p >= 0; --p)
    free(arr[p]);
  free(arr);
}
