#include "double.h"
#include "jagged.h"

void double_array_compress_to_sparse_array(
  double * b, const jagged1 * positions, const double * a)
{
  int i, positions_a0;
  int * positions_a1;

  positions_a0 = positions->a0;
  positions_a1 = positions->a1;

  for (i = 0; i < positions_a0; ++i)
    b[i] = a[positions_a1[i]];
}
