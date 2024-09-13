#include <stdio.h>
#include <stdlib.h>

#include "mesh_qc.h"

/* calculate vector f, f_i := (N^i \_/ sigma^d)[M]*/
void mesh_qc_vector_from_integral_of_basis_0_cup_d_cochain(
  double * f,
  const mesh_qc * m,
  const double * coefficients_d)
{
  int d, i, j, j_local, m_cn_0;
  double f_i, pow_2_d;
  jagged1 m_fc_0_d_i;
  jagged2 m_fc_0_d;

  d = m->dim;
  pow_2_d = (double) (1 << d);
  m_cn_0 = m->cn[0];
  mesh_fc_part2(&m_fc_0_d, m, 0, d);

  for (i = 0; i < m_cn_0; ++i)
  {
    f_i = 0;
    jagged2_part1(&m_fc_0_d_i, &m_fc_0_d, i);
    for (j_local = 0; j_local < m_fc_0_d_i.a0; ++j_local)
    {
      j = m_fc_0_d_i.a1[j_local];
      f_i += coefficients_d[j];
    }
    f[i] = f_i / pow_2_d;
  }
}
