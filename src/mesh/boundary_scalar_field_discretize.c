#include "boundary_scalar_field_discretize.h"

void boundary_scalar_field_discretize(
  double * result,
  int m_dim_embedded,
  const double * m_coord,
  const jagged1 * boundary_nodes,
  scalar_field g)
{
  int j, j_loc, boundary_nodes_a0;
  int * boundary_nodes_a1;
  
  boundary_nodes_a0 = boundary_nodes->a0;
  boundary_nodes_a1 = boundary_nodes->a1;
  
  for (j_loc = 0; j_loc < boundary_nodes_a0; ++j_loc)
  {
    j = boundary_nodes_a1[j_loc];
    result[j_loc] = g(m_coord + m_dim_embedded * j);
  }
}
