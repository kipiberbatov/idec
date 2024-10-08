#include "int.h"

void int_array_compress_to_sparse_array(
  int * b, int size, const int * positions, const int * a)
{
  int i;

  for (i = 0; i < size; ++i)
    b[i] = a[positions[i]];
}
