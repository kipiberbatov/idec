#include <string.h>

#include "double.h"
#include "polytope.h"
#include "unsigned_approximation.h"

void unsigned_approximation_of_scalar_field_on_nonzero_cells(
  double * x, const mesh * m, double (*f)(const double *), int p)
{
  int i, m_cn_p, m_dim_embedded;
  double center[MAX_DIM];
  double * m_coord;
  jagged1 m_cf_p_0_i;
  jagged2 m_cf_p_0;

  m_cn_p = m->cn[p];
  m_dim_embedded = m->dim_embedded;
  m_coord = m->coord;
  mesh_cf_part2(&m_cf_p_0, m, p, 0);
  m_cf_p_0_i.a1 = m_cf_p_0.a2;

  for (i = 0; i < m_cn_p; ++i)
  {
    m_cf_p_0_i.a0 = m_cf_p_0.a1[i];
    memset(center, 0, sizeof(double) * m_dim_embedded);
    polytope_coordinates_arithmetic_mean(
      center, m_dim_embedded, &m_cf_p_0_i, m_coord);
    x[i] = f(center);
    m_cf_p_0_i.a1 += m_cf_p_0_i.a0;
  }
}
