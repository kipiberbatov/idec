#include "jagged.h"

void jagged2_node_neighbors(
  int * node_neighbors,
  const jagged2 * edges_to_nodes,
  int i,
  const jagged1 * node_i_edges)
{
  int j, j_local, size_i;
  int * values_i;
  jagged1 edges_to_nodes_j;

  size_i = node_i_edges->a0;
  values_i = node_i_edges->a1;
  
  for (j_local = 0; j_local < size_i; ++ j_local)
  {
    j = values_i[j_local];
    jagged2_part1(&edges_to_nodes_j, edges_to_nodes, j);
    node_neighbors[j_local] = jagged1_couple_other_object(&edges_to_nodes_j, i);
  }
}
