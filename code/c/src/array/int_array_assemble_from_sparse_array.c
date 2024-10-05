#include "int.h"

void int_array_assemble_from_sparse_array(
  int * b, int size, const int * positions, const int * a)
{
  int i;

  for (i = 0; i < size; ++i)
    b[positions[i]] = a[i];
}
