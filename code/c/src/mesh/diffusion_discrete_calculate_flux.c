#include <errno.h>
#include <math.h>
#include <stdlib.h>

#include "diffusion_discrete_calculate_flux.h"

double * diffusion_discrete_calculate_flux(
  const mesh * m,
  matrix_sparse * m_cbd,
  int number_of_steps,
  const double * temperature)
{
  int i, j, m_cn_0, m_cn_1, n0, n1;
  double * flux, * flux_i;
  const double * temperature_i;
  jagged1 m_cf_1_0_j;
  jagged2 m_cf_1_0;

  mesh_cf_part2(&m_cf_1_0, m, 1, 0);

  m_cn_0 = m->cn[0];
  m_cn_1 = m->cn[1];
  flux = (double *) malloc(sizeof(double) * m_cn_1 * (number_of_steps + 1));
  if (errno)
  {
    fprintf(stderr, "Cannot allocate memory for flux");
    return NULL;
  }
  for (i = 0; i <= number_of_steps; ++i)
  {
    flux_i = flux + i * m_cn_1;
    temperature_i = temperature + i * m_cn_0;
    for (j = 0; j < m_cn_1; ++j)
    {
      jagged2_part1(&m_cf_1_0_j, &m_cf_1_0, j);
      n0 = m_cf_1_0_j.a1[0];
      n1 = m_cf_1_0_j.a1[1];
      flux_i[j] = fabs(temperature_i[n1] - temperature_i[n0]);
    }
  }
  return flux;
}
