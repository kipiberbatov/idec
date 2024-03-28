#include "spacetime_pde.h"

void spacetime_pde_boundary_vector(
  double * result,
  int m_dim_embedded,
  const double * m_coord,
  const jagged1 * m_boundary_nodes,
  scalar_field g_d)
{
  int j, j_loc, m_boundary_nodes_a0;
  int * m_boundary_nodes_a1;
  
  m_boundary_nodes_a0 = m_boundary_nodes->a0;
  m_boundary_nodes_a1 = m_boundary_nodes->a1;
  
  for (j_loc = 0; j_loc < m_boundary_nodes_a0; ++j_loc)
  {
    j = m_boundary_nodes_a1[j_loc];
    result[j_loc] = g_d(m_coord + m_dim_embedded * j);
  }
}
