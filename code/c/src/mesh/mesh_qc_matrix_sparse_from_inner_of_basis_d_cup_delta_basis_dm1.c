#include <stdlib.h>

#include "color.h"
#include "mesh_qc.h"

matrix_sparse *
mesh_qc_matrix_sparse_from_inner_of_basis_d_cup_delta_basis_dm1(
  const mesh_qc * m,
  const matrix_sparse * m_bd_d,
  const double * m_inner_d)
{
  int a_col_j, d, i_local, j, m_cn_d, pow_2_d;
  double m_inner_d_j;
  double * a_values;
  matrix_sparse * a, * b;

  d = m->dim;
  pow_2_d = 1 << d;
  m_cn_d = m->cn[d];

  a = matrix_sparse_copy(m_bd_d);
  if (a == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot copy m_bd_d : C_d -> C_{d - 1}\n", stderr);
    return NULL;
  }

  a_values = a->values;
  for (j = 0; j < m_cn_d; ++j)
  {
    a_col_j = pow_2_d * j;
    m_inner_d_j = m_inner_d[j];
    for (i_local = 0; i_local < pow_2_d; ++i_local)
      a_values[a_col_j + i_local] *= -m_inner_d_j;
  }

  b = matrix_sparse_transpose(a);
  if (b == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot transpose a\n", stderr);
  }
  matrix_sparse_free(a);
  return b;
}
