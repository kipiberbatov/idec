#include <stdio.h>
#include "simplex.h"

void simplex_centroid(double * s_centroid, const simplex * s)
{
  int node, nodes_number, s_dim_embedded, t, tmp;
  double * s_coord;
  
  nodes_number = s->dim + 1;
  s_dim_embedded = s->dim_embedded;
  s_coord = s->coord;
  for (node = 0; node < nodes_number; ++node)
  {
    tmp = node * s_dim_embedded;
    for (t = 0; t < s_dim_embedded; ++t)
      s_centroid[t] += s_coord[tmp + t];
  }
  for (t = 0; t < s_dim_embedded; ++t)
    s_centroid[t] /= nodes_number;
}
