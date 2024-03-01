#include "vector_sparse.h"

void vector_sparse_array2_fprint(
  FILE * out, int a0, const int * a1,
  vector_sparse *** arr, const char * format)
{
  int i;
  
  for (i = 0; i < a0; ++i)
    vector_sparse_array_fprint(out, a1[i], arr[i], format);
}
