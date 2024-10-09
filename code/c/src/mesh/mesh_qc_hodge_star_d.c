#include "mesh_qc.h"

void mesh_qc_hodge_star_d(
  double * cochain_0,
  const mesh_qc * m,
  const double * m_vol_d,
  const double * cochain_d)
{
  int d, i, j, j_local;
  int * m_fc_0_d_i;
  double numerator_i, denominator_i;
  jagged2 m_fc_0_d;

  d = m->dim;
  mesh_fc_part2(&m_fc_0_d, m, 0, d);
  m_fc_0_d_i = m_fc_0_d.a2;
  for (i = 0; i < m_fc_0_d.a0; ++i)
  {
    numerator_i = 0.;
    denominator_i = 0.;
    for (j_local = 0; j_local < m_fc_0_d.a1[i]; ++j_local)
    {
      j = m_fc_0_d_i[j_local];
      numerator_i += cochain_d[j];
      denominator_i += m_vol_d[j];
    }
    cochain_0[i] = numerator_i / denominator_i;
    m_fc_0_d_i += m_fc_0_d.a1[i];
  }
}
