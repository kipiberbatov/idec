#include "jagged.h"

int jagged1_relative_sign(const jagged1 * cell_nodes,
                          const jagged1 * hyperface_nodes)
{
  int rest_node, rest_node_position, sign0, sign1, sign2;
  int hyperface_nodes_messed_a1[4];
  jagged1 hyperface_nodes_messed;

  rest_node = jagged1_complement_simplicial(cell_nodes, hyperface_nodes);
  rest_node_position = jagged1_position(cell_nodes, rest_node);
  hyperface_nodes_messed.a0 = hyperface_nodes->a0;
  hyperface_nodes_messed.a1 = hyperface_nodes_messed_a1;
  jagged1_delete(&hyperface_nodes_messed, cell_nodes, rest_node_position);
  sign0 = (rest_node_position % 2 == 0) ? 1 : -1;
  sign1 = jagged1_signature(&hyperface_nodes_messed);
  sign2 = jagged1_signature(hyperface_nodes);
  return sign0 * sign1 * sign2;
}
