#include "mesh.h"

void mesh_boundary_node_coordinate_vectors_matrix(
  double * l,
  const mesh * m,
  int i,
  const int * node_i_neighbors,
  const jagged1 * node_i_edges)
{
  int i0, j_local, m_dim_embedded, s, size_i;
  double * l_j_local, * m_coord, * m_coord_i, * m_coord_i0;

  m_dim_embedded = m->dim_embedded;
  m_coord = m->coord;
  m_coord_i = m->coord + m_dim_embedded * i;
  size_i = node_i_edges->a0;

  for (j_local = 0; j_local < size_i; ++ j_local)
  {
    i0 = node_i_neighbors[j_local];
    m_coord_i0 = m_coord + m_dim_embedded * i0;
    l_j_local = l + m_dim_embedded * j_local;
    for (s = 0; s < m_dim_embedded; ++s)
      l_j_local[s] = m_coord_i[s] - m_coord_i0[s];
  }
}
