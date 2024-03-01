#include "mesh_qc_private.h"

static void mesh_qc_hodge_p_cols_total_d(
  int * m_hodge_p_cols_total, const mesh * m)
{
  int i, m_cn_d, d_exp;
  
  m_cn_d = m->cn[m->dim];
  d_exp = 1 << m->dim;
  for (i = 0; i <= m_cn_d; ++i)
    m_hodge_p_cols_total[i] = d_exp * i;
}

static void mesh_qc_hodge_p_cols_total_not_d(
  int * m_hodge_p_cols_total, const mesh * m, int p)
{
  int i, m_cn_p, p_exp;
  jagged1 m_fc_p_d_i;
  jagged2 m_fc_p_d;
  
  m_cn_p = m->cn[p];
  p_exp = 1 << p;
  mesh_fc_part2(&m_fc_p_d, m, p, m->dim);
  
  m_hodge_p_cols_total[0] = 0;
  for (i = 0; i < m_cn_p; ++i)
  {
    jagged2_part1(&m_fc_p_d_i, &m_fc_p_d, i);
    m_hodge_p_cols_total[i + 1] = 
      m_hodge_p_cols_total[i] + m_fc_p_d_i.a0 * p_exp;
  }
}

void mesh_qc_hodge_p_cols_total(
  int * m_hodge_p_cols_total, const mesh * m, int p)
{ 
  if (p == m->dim)
    mesh_qc_hodge_p_cols_total_d(m_hodge_p_cols_total, m);
  else
    mesh_qc_hodge_p_cols_total_not_d(m_hodge_p_cols_total, m, p);
}
