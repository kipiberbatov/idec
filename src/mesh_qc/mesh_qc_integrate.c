#include "mesh_qc.h"

double mesh_qc_integrate(const mesh_qc * m, const double * m_vol_d,
                         const vector_sparse * a)
{
  int a_nonzero_max, i, i_loc, j, t;
  int * a_positions;
  double sum, sum_loc;
  double * a_values;
  jagged1 m_cf_0_d_j;
  jagged2 m_cf_0_d;
  
  a_nonzero_max = a->nonzero_max;
  a_positions = a->positions;
  a_values = a->values;
  mesh_fc_part2(&m_cf_0_d, m, 0, m->dim);
  sum = 0.;
  for (t = 0; t < a_nonzero_max; ++t)
  {
    sum_loc = 0;
    j = a_positions[t];
    jagged2_part1(&m_cf_0_d_j, &m_cf_0_d, j);
    for (i_loc = 0; i_loc < m_cf_0_d_j.a0; ++i_loc)
    {
      i = m_cf_0_d_j.a1[i_loc];
      sum_loc += m_vol_d[i];
    }
    sum += a_values[t] * sum_loc;
  }
  return sum / (1 << m->dim);
}
