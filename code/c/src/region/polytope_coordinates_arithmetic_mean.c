#include "polytope.h"

void polytope_coordinates_arithmetic_mean(
  double * result,
  int embedding_dimension,
  const jagged1 * nodes,
  const double * coordinates)
{
  int node, nodes_a0, t, tmp;
  int * nodes_a1;

  nodes_a0 = nodes->a0;
  nodes_a1 = nodes->a1;
  for (node = 0; node < nodes_a0; ++node)
  {
    tmp = nodes_a1[node] * embedding_dimension;
    for (t = 0; t < embedding_dimension; ++t)
      result[t] += coordinates[tmp + t];
  }
  for (t = 0; t < embedding_dimension; ++t)
    result[t] /= nodes_a0;
}
