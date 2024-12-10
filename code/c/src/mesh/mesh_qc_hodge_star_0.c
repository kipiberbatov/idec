#include "mesh_qc.h"

void mesh_qc_hodge_star_0(
  double * cochain_d,
  const mesh_qc * m,
  const double * m_vol_d,
  const double * cochain_0)
{
  int d, i, j, j_local;
  int * m_cf_d_0_i;
  double value_i, pow_2_d;
  jagged2 m_cf_d_0;

  d = m->dim;
  pow_2_d = (double) (1 << d);
  mesh_cf_part2(&m_cf_d_0, m, d, 0);
  m_cf_d_0_i = m_cf_d_0.a2;
  for (i = 0; i < m_cf_d_0.a0; ++i)
  {
    value_i = 0.;
    for (j_local = 0; j_local < m_cf_d_0.a1[i]; ++j_local)
    {
      j = m_cf_d_0_i[j_local];
      value_i += cochain_0[j];
    }
    cochain_d[i] = value_i * m_vol_d[i] / pow_2_d;
    m_cf_d_0_i += m_cf_d_0.a1[i];
  }
}
