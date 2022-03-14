#include "mesh_brick.h"

mesh * mesh_brick_regular(int d, int n)
{
  int p;
  int n_list[MAX_DIM];
  double brick_lengths[MAX_DIM];
  mesh * m;
  
  for (p = 0; p < d; ++p)
    n_list[p] = n;
  for (p = 0; p < d; ++p)
    brick_lengths[p] = 1.;
  m = mesh_brick(d, brick_lengths, n_list);
  /* NULL pointer check */
  return m;
}
