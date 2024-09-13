#include "boundary_pseudoscalar_field_discretize.h"

void boundary_pseudoscalar_field_discretize(
  double * result,
  const mesh * m,
  const double * m_vol_dm1,
  const jagged1 * boundary_hyperfaces,
  double (*g)(const double *))
{
  int i, i_local, j, j_local, boundary_hyperfaces_a0, m_dim_embedded;
  int * boundary_hyperfaces_a1;
  double * m_coord;
  jagged1 m_cf_dm1_0_i;
  jagged2 m_cf_dm1_0;

  m_dim_embedded = m->dim_embedded;
  m_coord = m->coord;
  boundary_hyperfaces_a0 = boundary_hyperfaces->a0;
  boundary_hyperfaces_a1 = boundary_hyperfaces->a1;
  mesh_cf_part2(&m_cf_dm1_0, m, m->dim - 1, 0);

  for (i_local = 0; i_local < boundary_hyperfaces_a0; ++i_local)
  {
    result[i_local] = 0;
    i = boundary_hyperfaces_a1[i_local];
    jagged2_part1(&m_cf_dm1_0_i, &m_cf_dm1_0, i);
    for (j_local = 0; j_local < m_cf_dm1_0_i.a0; ++j_local)
    {
      j = m_cf_dm1_0_i.a1[i_local];
      result[i_local] += g(m_coord + m_dim_embedded * j);
    }
    result[i_local] /= m_vol_dm1[i];
  }
}
