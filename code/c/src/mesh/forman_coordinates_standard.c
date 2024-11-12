#include <string.h>

#include "forman_coordinates_private.h"
#include "polytope.h"

/* Calculate the Forman coordinates as arithmetic means of cell nodes */
void forman_coordinates_standard(double * m_forman_coordinates, const mesh * m)
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

  memcpy(m_forman_coordinates,
    m_coord, sizeof(double) * m_dim_embedded * m_cn[0]);

  ind = m_dim_embedded * m_cn[0];
  for (p = 1; p <= m_dim; ++p)
  {
    mesh_cf_part2(&m_cf_p_0, m, p, 0);
    m_cn_p = m_cn[p];
    for (i = 0; i < m_cn_p; ++i)
    {
      jagged2_part1(&m_cf_p_0_i, &m_cf_p_0, i);
      polytope_coordinates_arithmetic_mean(
        m_forman_coordinates + ind, m_dim_embedded, &m_cf_p_0_i, m_coord);
      ind += m_dim_embedded;
    }
  }
}
