#include "double.h"

void double_array_add_sparse_to(
  double * f, const jagged1 * indices, const double * g)
{
  int i, i_local, indices_a0;
  int * indices_a1;

  indices_a0 = indices->a0;
  indices_a1 = indices->a1;
  for (i_local = 0; i_local < indices_a0; ++i_local)
  {
    i = indices_a1[i_local];
    f[i] += g[i_local];
  }
}
