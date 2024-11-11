#include "unsigned_approximation.h"

void unsigned_approximation_of_scalar_field_on_1_cells(
  double * x, const mesh * m, double (*f)(const double *))
{
  int i, i0, i1, m_cn_1, m_dim_embedded;
  int * m_cf_1_0_i;
  double x0, x1;
  double * m_coord;
  jagged2 m_cf_1_0;

  m_cn_1 = m->cn[1];
  m_dim_embedded = m->dim_embedded;
  m_coord = m->coord;
  mesh_cf_part2(&m_cf_1_0, m, 1, 0);
  m_cf_1_0_i = m_cf_1_0.a2;

  for (i = 0; i < m_cn_1; ++i)
  {
    i0 = m_cf_1_0_i[0];
    i1 = m_cf_1_0_i[1];
    x0 = f(m_coord + m_dim_embedded * i0);
    x1 = f(m_coord + m_dim_embedded * i1);
    x[i] = (x0 + x1) / 2;
    m_cf_1_0_i += m_cf_1_0.a1[i];
  }
}
