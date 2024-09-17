#include "de_rham.h"

void de_rham_nonzero(
  double * x,
  const mesh * m,
  int p,
  const double * m_vol_p,
  double (*f)(const double *))
{
  int i, j, j_local, m_cn_p, m_dim_embedded;
  double tmp;
  double * m_coord;
  jagged1 m_cf_p_0_i;
  jagged2 m_cf_p_0;

  m_dim_embedded = m->dim_embedded;
  m_coord = m->coord;
  m_cn_p = m->cn[p];
  mesh_cf_part2(&m_cf_p_0, m, p, 0);

  for (i = 0; i < m_cn_p; ++i)
  {
    tmp = 0;
    jagged2_part1(&m_cf_p_0_i, &m_cf_p_0, i);
    for (j_local = 0; j_local < m_cf_p_0_i.a0; ++j_local)
    {
      j = m_cf_p_0_i.a1[j_local];
      tmp += f(m_coord + m_dim_embedded * j);
    }
    tmp *= m_vol_p[i] / (double) m_cf_p_0_i.a0;
    x[i] = tmp;
  }
}
