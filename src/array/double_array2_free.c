#include <stdlib.h>
#include "double.h"

void double_array2_free(double ** arr, int n)
{
  int p;
  
  for (p = n - 1; p >= 0; --p)
    free(arr[p]);
  free(arr);
}
