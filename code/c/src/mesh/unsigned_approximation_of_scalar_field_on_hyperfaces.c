#include <string.h>

#include "double.h"
#include "polytope.h"
#include "unsigned_approximation.h"

void unsigned_approximation_of_scalar_field_on_hyperfaces(
  double * x, const mesh * m, double (*f)(const double *))
{
  int dm1, i, m_cn_dm1, m_dim_embedded;
  double center[MAX_DIM];
  double * m_coord;
  jagged1 m_cf_dm1_0_i;
  jagged2 m_cf_dm1_0;

  dm1 = m->dim - 1;
  m_cn_dm1 = m->cn[dm1];
  m_dim_embedded = m->dim_embedded;
  m_coord = m->coord;
  mesh_cf_part2(&m_cf_dm1_0, m, dm1, 0);
  m_cf_dm1_0_i.a1 = m_cf_dm1_0.a2;

  for (i = 0; i < m_cn_dm1; ++i)
  {
    m_cf_dm1_0_i.a0 = m_cf_dm1_0.a1[i];
    memset(center, 0, sizeof(double) * m_dim_embedded);
    polytope_coordinates_arithmetic_mean(
      center, m_dim_embedded, &m_cf_dm1_0_i, m_coord);
    x[i] = f(center);
    m_cf_dm1_0_i.a1 += m_cf_dm1_0_i.a0;
  }
}
