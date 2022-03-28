#include <stdlib.h>
#include "vector_sparse.h"

void vector_sparse_array_free(vector_sparse ** arr, int a0)
{
  int i;

  for (i = a0 - 1; i >= 0; --i)
    vector_sparse_free(arr[i]);
  free(arr);
}
