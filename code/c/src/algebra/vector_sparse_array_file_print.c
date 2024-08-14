#include "vector_sparse.h"

void vector_sparse_array_file_print(
  FILE * out, int a0, vector_sparse ** arr, const char * format)
{
  int i;

  for (i = 0; i < a0; ++i)
    vector_sparse_file_print(out, arr[i], format);
}
