#include <stdlib.h>
#include "int.h"

void int_array2_free(int ** arr, int a0)
{
  int p;

  for (p = a0 - 1; p >= 0; --p)
    free(arr[p]);
  free(arr);
}
