#include "vector_sparse.h"

void vector_sparse_array_fprint(
  FILE * out, int a0, vector_sparse ** arr, const char * format)
{
  int i;
  
  for (i = 0; i < a0; ++i)
    vector_sparse_fprint(out, arr[i], format);
}
