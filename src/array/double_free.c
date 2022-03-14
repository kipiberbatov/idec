#include <stdlib.h>
#include "double.h"

void double_free_array2(double ** arr, int a0)
{
  int p;
  
  for (p = a0 - 1; p >= 0; --p)
    free(arr[p]);
  free(arr);
}
