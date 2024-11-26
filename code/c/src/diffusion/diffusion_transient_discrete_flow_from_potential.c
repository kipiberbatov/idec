#include <stdlib.h>

#include "color.h"
#include "double.h"
#include "diffusion_steady_state_discrete_dual_flow_from_potential.h"
#include "diffusion_transient_discrete_flow_from_potential.h"

void diffusion_transient_discrete_flow_from_potential(
  double * flow,
  const mesh * m,
  const matrix_sparse * m_bd_1,
  const double * kappa_1,
  const double * potential,
  const matrix_sparse * m_hodge_1,
  int number_of_steps)
{
  int i, m_cn_0, m_cn_dm1;
  double * dual_flow_i, * flow_i;
  const double * potential_i;

  dual_flow_i = (double *) malloc(sizeof(double) * m->cn[1]);
  if (dual_flow_i == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %ld bytels of memory for dual_flow_i\n",
      sizeof(double) * m->cn[1]);
    return;
  }

  m_cn_0 = m->cn[0];
  m_cn_dm1 = m->cn[m->dim - 1];
  for (i = 0; i <= number_of_steps; ++i)
  {
    potential_i = potential + m_cn_0 * i;
    flow_i = flow + m_cn_dm1 * i;
    diffusion_steady_state_discrete_dual_flow_from_potential(
      dual_flow_i, m, m_bd_1, kappa_1, potential_i);
    matrix_sparse_vector_multiply_add(flow_i, m_hodge_1, dual_flow_i);
  }

  free(dual_flow_i);
}
