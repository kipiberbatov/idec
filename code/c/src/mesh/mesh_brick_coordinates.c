#include "int.h"
#include "mesh_brick_private.h"

static void set_node_coordinates(double * m_coordinates, int * index,
  int d, const int * node, const double * units)
{
  int p;
  double * point;

  point = m_coordinates + *index;
  for (p = 0; p < d; ++p)
    point[p] = ((double) node[p]) * units[p];
  *index += d;
}

void mesh_brick_coordinates(double * m_coordinates,
  int d, const double * brick_lengths, const int * partitions)
{
  int index, node_index, nodes_total, p;
  int node[MAX_DIM], nodes_per_direction[MAX_DIM];
  double units[MAX_DIM];

  for (p = 0; p < d; ++p)
    units[p] = brick_lengths[p] / ((double) partitions[p]);

  for (p = 0; p < d; ++p)
    nodes_per_direction[p] = partitions[p] + 1;

  int_array_assign_constant(node, d, 0);
  nodes_total = int_array_total_product(d, nodes_per_direction);

  index = 0;
  node_index =0;
  while (node_index < nodes_total - 1)
  {
    set_node_coordinates(m_coordinates, &index, d, node, units);
    int_array_cartesian_product_next(node, d, nodes_per_direction);
    ++node_index;
  }
  set_node_coordinates(m_coordinates, &index, d, node, units);
}
