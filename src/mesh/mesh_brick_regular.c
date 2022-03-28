#include <errno.h>
#include "double.h"
#include "int.h"
#include "mesh_brick.h"

mesh * mesh_brick_regular(int d, int n)
{
  int n_list[MAX_DIM];
  double brick_lengths[MAX_DIM];
  mesh * m;
  
  int_array_assign_constant(n_list, d, n);
  double_array_assign_constant(brick_lengths, d, 1.);
  m = mesh_brick(d, brick_lengths, n_list);
  if (errno)
  {
    fputs("mesh_brick_regular - cannot calculate m\n", stderr);
    return NULL;
  }
  return m;
}
