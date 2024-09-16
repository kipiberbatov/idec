#include "mesh_qc.h"

/*
calculate diagonal matrix a,
a_{i, j} := <c^{d - 1, j}, pi_{d - 1}^{-1} c^{d - 1 i}>
*/
void mesh_qc_matrix_diagonal_from_inner_of_basis_0_cup_pi_0_basis_0(
  double * a,
  const mesh * m,
  const double * m_inner_0,
  const double * pi_0)
{
  int i, m_cn_0;

  m_cn_0 = m->cn[0];
  for (i = 0; i < m_cn_0; ++i)
    a[i] = m_inner_0[i] * pi_0[i];
}
