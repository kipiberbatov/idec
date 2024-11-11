#include "diffusion_transient_discrete_primal_edge_flux.h"

void diffusion_transient_discrete_primal_edge_flux(
  double * flux,
  const mesh * m,
  const matrix_sparse * m_bd_1,
  const double * pi_1,
  int number_of_steps,
  const double * temperature)
{
  int i, j, m_cn_0, m_cn_1, n0, n1;
  int * m_bd_1_cols_total, * m_cf_1_0_j;
  double sign;
  double * flux_i, * m_bd_1_values;
  const double * temperature_i;
  jagged2 m_cf_1_0;

  mesh_cf_part2(&m_cf_1_0, m, 1, 0);
  m_cn_0 = m->cn[0];
  m_cn_1 = m->cn[1];
  m_bd_1_cols_total = m_bd_1->cols_total;
  m_bd_1_values = m_bd_1->values;

  for (i = 0; i <= number_of_steps; ++i)
  {
    flux_i = flux + i * m_cn_1;
    temperature_i = temperature + i * m_cn_0;
    m_cf_1_0_j = m_cf_1_0.a2;
    for (j = 0; j < m_cn_1; ++j)
    {
      sign = m_bd_1_values[m_bd_1_cols_total[j]];
      n0 = m_cf_1_0_j[0];
      n1 = m_cf_1_0_j[1];
      flux_i[j] = sign * pi_1[j] * (temperature_i[n0] - temperature_i[n1]);
      m_cf_1_0_j += m_cf_1_0.a1[j];
    }
  }
}
