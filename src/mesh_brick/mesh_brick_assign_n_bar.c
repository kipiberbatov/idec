#include "int.h"
#include "mesh_brick_private.h"

void mesh_brick_assign_n_bar(
  int * n_bar, int d, const int * n, int p, const int * a)
{
  int r;
  
  for (r = 0; r < d; ++r)
    n_bar[r] = (int_array_member(p, a, r)) ? n[r] : (n[r] + 1);
}
