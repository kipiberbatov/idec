#include "mesh_qc.h"

void mesh_qc_vector_from_inner_of_basis_d_cup_d_cochain(
  double * f,
  const mesh_qc * m,
  const double * m_inner_d,
  const double * coefficients_d)
{
  int d, i, m_cn_d;

  d = m->dim;
  m_cn_d = m->cn[d];

  for (i = 0; i < m_cn_d; ++i)
    f[i] = m_inner_d[i] * coefficients_d[i];
}
