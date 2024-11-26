#include "mesh_qc.h"

/*
calculate diagonal matrix a,
a_{i, j} := <c^{d - 1, j}, pi_{d - 1}^{-1} c^{d - 1 i}>
*/
void mesh_qc_matrix_diagonal_from_inner_of_basis_dm1_cup_inverse_pi_2_basis_dm1(
  double * a,
  const mesh * m,
  const double * m_inner_dm1,
  const double * kappa_dm1)
{
  int i, m_cn_dm1;

  m_cn_dm1 = m->cn[m->dim - 1];
  for (i = 0; i < m_cn_dm1; ++i)
    a[i] = m_inner_dm1[i] / kappa_dm1[i];
}
