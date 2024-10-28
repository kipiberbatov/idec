#include <stdlib.h>

#include "color.h"
#include "diffusion_steady_state_discrete_primal_flow_from_potential.h"

static void diffusion_steady_state_discrete_primal_pseudo_flow_from_potential(
  double * pseudo_flow,
  const mesh * m,
  const matrix_sparse * m_bd_1,
  const double * pi_1,
  const double * potential)
{
  int i, j0, j1, m_cn_1;
  int * m_bd_1_cols_total, * m_cf_1_0_i;
  double sign;
  double * m_bd_1_values;
  jagged2 m_cf_1_0;

  mesh_cf_part2(&m_cf_1_0, m, 1, 0);
  m_cn_1 = m->cn[1];
  m_bd_1_cols_total = m_bd_1->cols_total;
  m_bd_1_values = m_bd_1->values;
  m_cf_1_0_i = m_cf_1_0.a2;

  for (i = 0; i < m_cn_1; ++i)
  {
    sign = m_bd_1_values[m_bd_1_cols_total[i]];
    j0 = m_cf_1_0_i[0];
    j1 = m_cf_1_0_i[1];
    pseudo_flow[i] = sign * pi_1[i] * (potential[j0] - potential[j1]);
    m_cf_1_0_i += m_cf_1_0.a1[i];
  }
}

void diffusion_steady_state_discrete_primal_flow_from_potential(
  double * flow,
  const mesh * m,
  const matrix_sparse * m_bd_1,
  const double * pi_1,
  const double * potential,
  const matrix_sparse * m_hodge_1)
{
  double * pseudo_flow;

  pseudo_flow = (double *) malloc(sizeof(double) * m->cn[1]);
  if (pseudo_flow == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %ld bytels of memory for pseudo_flow\n",
      sizeof(double) * m->cn[1]);
    return;
  }

  diffusion_steady_state_discrete_primal_pseudo_flow_from_potential(
    pseudo_flow, m, m_bd_1, pi_1, potential);

  matrix_sparse_vector_multiply_add(flow, m_hodge_1, pseudo_flow);
  free(pseudo_flow);
}
