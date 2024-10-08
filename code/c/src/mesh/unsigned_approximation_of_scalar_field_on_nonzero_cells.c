#include "double.h"
#include "unsigned_approximation.h"

void unsigned_approximation_of_scalar_field_on_nonzero_cells(
  double * x, const mesh * m, double (*f)(const double *), int p)
{
  int i, j, j_local, m_cn_p, m_dim_embedded;
  double coefficient_i;
  double center[MAX_DIM] = {0};
  double * m_coord, * m_coord_j;
  jagged1 m_cf_p_0_i;
  jagged2 m_cf_p_0;

  m_cn_p = m->cn[p];
  m_dim_embedded = m->dim_embedded;
  m_coord = m->coord;
  mesh_cf_part2(&m_cf_p_0, m, p, 0);

  for (i = 0; i < m_cn_p; ++i)
  {
    jagged2_part1(&m_cf_p_0_i, &m_cf_p_0, i);
    for (j_local = 0; j_local < m_cf_p_0_i.a0; ++j_local)
    {
      j = m_cf_p_0_i.a1[j_local];
      m_coord_j = m_coord + m_dim_embedded * j;
      double_array_add_to(center, m_dim_embedded, m_coord_j);
    }
    coefficient_i = 1. / (double) m_cf_p_0_i.a0;
    double_array_multiply_with(center, m_dim_embedded, coefficient_i);
    x[i] = f(center);
  }
}
