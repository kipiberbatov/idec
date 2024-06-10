// #include <errno.h>
// #include <stdlib.h>
#include <string.h>
#include "forman.h"
// #include "mesh_private.h"
// #include "simplex.h"
// #include "quasi_cube.h"

static void nodes_arithmetic_mean(double * result,
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

void forman_coord(double * m_forman_coord, const mesh * m)
{
  int i, ind, m_dim_embedded, m_dim, m_cn_p, p;
  int * m_cn;
  double * m_coord;
  jagged1 m_cf_p_0_i;
  jagged2 m_cf_p_0;
  
  m_dim_embedded = m->dim_embedded;
  m_dim = m->dim;
  m_cn = m->cn;
  m_coord = m->coord;
  
  memcpy(m_forman_coord, m_coord, sizeof(double) * m_dim_embedded * m_cn[0]);
  
  ind = m_dim_embedded * m_cn[0];
  for (p = 1; p <= m_dim; ++p)
  {
    mesh_cf_part2(&m_cf_p_0, m, p, 0);
    m_cn_p = m_cn[p];
    for (i = 0; i < m_cn_p; ++i)
    {
      jagged2_part1(&m_cf_p_0_i, &m_cf_p_0, i);
      nodes_arithmetic_mean(
        m_forman_coord + ind, m_dim_embedded, &m_cf_p_0_i, m_coord);
      ind += m_dim_embedded;
    }
  }
}

#if 0
/* finds the centroids of a simplicial mesh or of a quasi-cubical mesh */
/* m_forman_coord is set to zero initially */
void forman_coord(double * m_forman_coord, const mesh * m)
{
  int i, ind, m_dim_embedded, m_dim, m_cn_p, p;
  int * m_cn;
  double * m_coord;
  double s_coord[24]; /* m_dim_embeddded = 3 -> nodes = 8 -> product = 24 */
  simplex s;
  quasi_cube s2;
  jagged1 m_cf_p_0_i;
  jagged2 m_cf_p_0;
  
  m_dim_embedded = m->dim_embedded;
  m_dim = m->dim;
  m_cn = m->cn;
  m_coord = m->coord;
  
  s.dim_embedded = m_dim_embedded;
  s2.dim_embedded = m_dim_embedded;
  s.coord = s_coord;
  s2.coord = s_coord;
  
  memcpy(m_forman_coord, m_coord, sizeof(double) * m_dim_embedded * m_cn[0]);
  
  ind = m_dim_embedded * m_cn[0];
  for (p = 1; p <= m_dim; ++p)
  {
    s.dim = p;
    s2.dim = p;
    mesh_cf_part2(&m_cf_p_0, m, p, 0);
    m_cn_p = m_cn[p];
    for (i = 0; i < m_cn_p; ++i)
    {
      jagged2_part1(&m_cf_p_0_i, &m_cf_p_0, i);
      mesh_cell_coord(s_coord, &m_cf_p_0_i, m_dim_embedded, m_coord);
      if (m_cf_p_0_i.a0 == p + 1)
        simplex_centroid(m_forman_coord + ind, &s);
      else if (m_cf_p_0_i.a0 == (1 << p))
        quasi_cube_centroid(m_forman_coord + ind, &s2);
      ind += m_dim_embedded;
    }
  }
}
#endif
