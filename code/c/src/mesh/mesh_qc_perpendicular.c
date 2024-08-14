#include "mesh_qc_private.h"

/* Let c[d, k] be a volume around c[p, i].
 * Finds the combinatorially perpendicular cells of c[p, i] with respect to
 * c[d, k] and the nodes they intersect at.
 */
void mesh_qc_perpendicular(
  int * nodes, int * perp, const jagged2 * m_cf_d_q, const jagged2 * m_cf_p_0,
  const jagged2 * m_cf_q_0, int i, int k)
{
  int ind, j, j_loc;
  jagged1 m_cf_d_q_k, m_cf_p_0_i, m_cf_q_0_j;

  jagged2_part1(&m_cf_d_q_k, m_cf_d_q, k);
  jagged2_part1(&m_cf_p_0_i, m_cf_p_0, i);
  ind = 0;
  for (j_loc = 0; j_loc < m_cf_d_q_k.a0; ++j_loc)
  {
    j = jagged1_part1(&m_cf_d_q_k, j_loc);
    jagged2_part1(&m_cf_q_0_j, m_cf_q_0, j);
    if (jagged1_intersection_count(&m_cf_p_0_i, &m_cf_q_0_j) == 1)
    {
      nodes[ind] = jagged1_intersection_unique(&m_cf_p_0_i, &m_cf_q_0_j);
      perp[ind] = j;
      ++ind;
    }
  }
}
