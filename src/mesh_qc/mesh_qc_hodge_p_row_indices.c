#include <string.h>
#include "mesh_qc_private.h"

static void mesh_qc_hodge_p_row_indices_d(
  int * m_hodge_p_row_indices, const mesh * m)
{
  int d_exp, i, ind, m_cn_d;
  jagged1 m_cf_d_0_i;
  jagged2 m_cf_d_0;
  
  m_cn_d = m->cn[m->dim];
  d_exp = 1 << m->dim;
  mesh_cf_part2(&m_cf_d_0, m, m->dim, 0);
  
  ind = 0;
  for (i = 0; i < m_cn_d; ++i)
  {
    jagged2_part1(&m_cf_d_0_i, &m_cf_d_0, i);
    memcpy(m_hodge_p_row_indices + ind, m_cf_d_0_i.a1, sizeof(int) * d_exp);
    ind += d_exp;
  }
}

static void mesh_qc_hodge_p_row_indices_0(
  int * m_hodge_p_row_indices, const mesh * m)
{
  int i, ind, m_cn_0;
  jagged1 m_fc_0_d_i;
  jagged2 m_fc_0_d;
  
  m_cn_0 = m->cn[0];
  mesh_fc_part2(&m_fc_0_d, m, 0, m->dim);
  
  ind = 0;
  for (i = 0; i < m_cn_0; ++i)
  {
    jagged2_part1(&m_fc_0_d_i, &m_fc_0_d, i);
    memcpy(m_hodge_p_row_indices + ind, m_fc_0_d_i.a1,
           sizeof(int) * m_fc_0_d_i.a0);
    ind += m_fc_0_d_i.a0;
  }
}

void mesh_qc_hodge_p_row_indices_nontrivial(
  int * m_hodge_p_row_indices, const mesh * m, int p)
{
  int i, ind, k, k_loc, m_cn_p, m_dim, p_exp, q;
  int nodes[8], perp[8]; /* #nodes(quasi_cube) = 2^3 = 8 */
  jagged1 m_fc_p_d_i;
  jagged2 m_cf_d_q, m_cf_p_0, m_cf_q_0, m_fc_p_d;
  
  m_dim = m->dim;
  m_cn_p = m->cn[p];
  p_exp = 1 << p;
  q = m_dim - p;
  mesh_fc_part2(&m_fc_p_d, m, p, m_dim);
  mesh_cf_part2(&m_cf_d_q, m, m_dim, q);
  mesh_cf_part2(&m_cf_p_0, m, p, 0);
  mesh_cf_part2(&m_cf_q_0, m, q, 0);
  
  ind = 0;
  for (i = 0; i < m_cn_p; ++i)
  {
    jagged2_part1(&m_fc_p_d_i, &m_fc_p_d, i);
    for (k_loc = 0; k_loc < m_fc_p_d_i.a0; ++k_loc)
    {
      k = m_fc_p_d_i.a1[k_loc];
      mesh_qc_perpendicular(nodes, perp, &m_cf_d_q, &m_cf_p_0, &m_cf_q_0, i, k);
      memcpy(m_hodge_p_row_indices + ind, perp, sizeof(int) * p_exp);
      ind += p_exp;
    }
  }
}

void mesh_qc_hodge_p_row_indices(
  int * m_hodge_p_row_indices, const mesh * m, int p)
{
  if (p == m->dim)
    mesh_qc_hodge_p_row_indices_d(m_hodge_p_row_indices, m);
  else if (p == 0)
    mesh_qc_hodge_p_row_indices_0(m_hodge_p_row_indices, m);
  else
    mesh_qc_hodge_p_row_indices_nontrivial(m_hodge_p_row_indices, m, p);
}
