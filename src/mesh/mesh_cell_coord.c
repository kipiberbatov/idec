#include <string.h>
#include "mesh_private.h"

void mesh_cell_coord(
  double * s_coord, const jagged1 * m_cf_p_0_i,
  int m_dim_embedded, const double * m_coord)
{
  int m_cf_p_0_i_a0, j_loc, tmp1, tmp2;
  int * m_cf_p_0_i_a1;

  m_cf_p_0_i_a0 = m_cf_p_0_i->a0;
  m_cf_p_0_i_a1 = m_cf_p_0_i->a1;

  for (j_loc = 0; j_loc < m_cf_p_0_i_a0; ++j_loc)
  {
    tmp1 = m_dim_embedded * j_loc;
    tmp2 = m_dim_embedded * m_cf_p_0_i_a1[j_loc];
    memcpy(s_coord + tmp1, m_coord + tmp2, sizeof(double) * m_dim_embedded);
  }
}
