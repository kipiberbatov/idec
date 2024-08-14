#include "jagged.h"

int jagged1_complement_simplicial(const jagged1 * cell_nodes,
                                  const jagged1 * hyperface_nodes)
{
  int cell_nodes_a0, i;
  int * cell_nodes_a1;

  cell_nodes_a0 = cell_nodes->a0;
  cell_nodes_a1 = cell_nodes->a1;
  for (i = 0; i < cell_nodes_a0; ++i)
    if(!jagged1_member(hyperface_nodes, cell_nodes_a1[i]))
      return cell_nodes_a1[i];
  return -1;
}
