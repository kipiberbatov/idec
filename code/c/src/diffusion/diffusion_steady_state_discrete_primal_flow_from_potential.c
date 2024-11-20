#include <stdlib.h>

#include "color.h"
#include "diffusion_steady_state_discrete_primal_flow_from_potential.h"
#include "diffusion_steady_state_discrete_primal_dual_flow.h"

void diffusion_steady_state_discrete_primal_flow_from_potential(
  double * flow,
  const mesh * m,
  const matrix_sparse * m_bd_1,
  const double * pi_1,
  const double * potential,
  const matrix_sparse * m_hodge_1)
{
  double * dual_flow;

  dual_flow = (double *) malloc(sizeof(double) * m->cn[1]);
  if (dual_flow == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %ld bytels of memory for dual_flow\n",
      sizeof(double) * m->cn[1]);
    return;
  }

  diffusion_steady_state_discrete_primal_dual_flow(
    dual_flow, m, m_bd_1, pi_1, potential);

  matrix_sparse_vector_multiply_add(flow, m_hodge_1, dual_flow);
  free(dual_flow);
}
