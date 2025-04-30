#include <string.h>

#include "int.h"
#include "mesh_parallelotope_grid.h"

static void set_node_coordinates(double * x, int * index,
  int d, int n, const double * origin,
  const double * directions, const int * partitions, const int * node)
{
  int p, s;
  double lambda_p;
  double * point;
  const double * e_p;

  point = x + *index;
  memcpy(point, origin, sizeof(double) * n);
  for (p = 0; p < d; ++p)
  {
    lambda_p = (double) node[p] / (double) partitions[p];
    e_p = directions + p * n;
    for (s = 0; s < n; ++s)
      point[s] += lambda_p * e_p[s];
  }
  *index += n;
}

/* $d$ is intrinsic dimension, $n$ is embedding dimension */
void mesh_parallelotope_grid_coordinates(
  double * x, /* of size $n * product_{p = 0}^{d - 1} partitions[p]$ */
  int d,
  int n,
  const double * origin, /* of size $n$ */
  const double * directions, /* of size $n * d$ */
  const int * partitions) /* of size $d$ */
{
  int index, node_index, nodes_total, p;
  int node[MAX_DIM], nodes_per_direction[MAX_DIM];

  for (p = 0; p < d; ++p)
    nodes_per_direction[p] = partitions[p] + 1;

  int_array_assign_constant(node, d, 0);
  nodes_total = int_array_total_product(d, nodes_per_direction);

  index = 0;
  node_index = 0;
  while (node_index < nodes_total - 1)
  {
    set_node_coordinates(x, &index, d, n, origin, directions, partitions, node);
    int_array_cartesian_product_next(node, d, nodes_per_direction);
    ++node_index;
  }
  set_node_coordinates(x, &index, d, n, origin, directions, partitions, node);
}
