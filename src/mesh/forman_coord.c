#include <stdlib.h>
#include "forman.h"
#include "list.h"
#include "simplex.h"
#include "quasi_cube.h"

static void simplex_get_coord(
  double * s_coord, const jagged1 * m_cell_nodes,
  int m_dim_embedded, const double * m_coord)
{
  int m_cell_nodes_a0, node, t, tmp1, tmp2;
  int * m_cell_nodes_a1;
  
  m_cell_nodes_a0 = m_cell_nodes->a0;
  m_cell_nodes_a1 = m_cell_nodes->a1;
  for (node = 0; node < m_cell_nodes_a0; ++node)
  {
    tmp1 = node * m_dim_embedded;
    tmp2 = m_cell_nodes_a1[node] * m_dim_embedded;
    for (t = 0; t < m_dim_embedded; ++t)
      s_coord[tmp1 + t] = m_coord[tmp2 + t];
  }          
}

static void quasi_cube_get_coord(
  double * s_coord, const jagged1 * m_cell_nodes,
  int m_dim_embedded, const double * m_coord)
{
  int m_cell_nodes_a0, node, t, tmp1, tmp2;
  int * m_cell_nodes_a1;
  
  m_cell_nodes_a0 = m_cell_nodes->a0;
  m_cell_nodes_a1 = m_cell_nodes->a1;
  for (node = 0; node < m_cell_nodes_a0; ++node)
  {
    tmp1 = node * m_dim_embedded;
    tmp2 = m_cell_nodes_a1[node] * m_dim_embedded;
    for (t = 0; t < m_dim_embedded; ++t)
      s_coord[tmp1 + t] = m_coord[tmp2 + t];
  }          
}

double * forman_coord(const mesh * m, const int * m_forman_cn)
{
  int i, ind, m_dim_embedded, m_dim, m_cn_p, p, size, t;
  int * m_cn;
  double * m_coord, * m_forman_coord;
  double s_coord[100];
  simplex s;
  quasi_cube s2;
  jagged1 m_cell_nodes;
  jagged2 m_cells_nodes;
  
  m_dim_embedded = m->dim_embedded;
  m_dim = m->dim;
  m_cn = m->cn;
  m_coord = m->coord;
  
  s.dim_embedded = m_dim_embedded;
  s2.dim_embedded = m_dim_embedded;
  
  size = m_forman_cn[0] * m_dim_embedded;
  m_forman_coord = (double *) calloc(size, sizeof(double));
  /* NULL pointer check */
  ind = 0;
  m_cn_p = m_cn[0];
  for (i = 0; i < m_cn_p; ++i)
  {
    for (t = 0; t < m_dim_embedded; ++t)
      m_forman_coord[ind + t] = m_coord[ind + t];
    ind += m_dim_embedded;
  }
  for (p = 1; p <= m_dim; ++p)
  {
    s.dim = p;
    s2.dim = p;
    m_cn_p = m_cn[p];
    mesh_cf_part2(&m_cells_nodes, m, p, 0);
    for (i = 0; i < m_cn_p; ++i)
    {
      jagged2_part1(&m_cell_nodes, &m_cells_nodes, i);
      if (m_cell_nodes.a0 == p + 1)
      {
        simplex_get_coord(s_coord, &m_cell_nodes, m_dim_embedded, m_coord);
        s.coord = s_coord;
        simplex_centroid(m_forman_coord + ind, &s);
      }
      else if (m_cell_nodes.a0 == (1 << p))
      {
        quasi_cube_get_coord(s_coord, &m_cell_nodes, m_dim_embedded, m_coord);
        s2.coord = s_coord;
        quasi_cube_centroid(m_forman_coord + ind, &s2);
      }
      ind += m_dim_embedded;
    }
  }
  return m_forman_coord;
}
