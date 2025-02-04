#include <stdlib.h>

#include "color.h"
#include "diffusion_steady_state_discrete_flow_from_potential.h"
#include "diffusion_steady_state_discrete_dual_flow_from_potential.h"
#include "idec_error_message.h"
#include "mesh.h"

void diffusion_steady_state_discrete_flow_from_potential(
  double * flow,
  const struct mesh * m,
  const struct matrix_sparse * m_bd_1,
  const double * kappa_1,
  const double * potential,
  const struct matrix_sparse * m_hodge_1)
{
  double * dual_flow;

  dual_flow = (double *) malloc(sizeof(double) * m->cn[1]);
  if (dual_flow == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    idec_error_message_malloc(sizeof(double) * m->cn[1], "dual_flow");
    return;
  }

  diffusion_steady_state_discrete_dual_flow_from_potential(
    dual_flow, m, m_bd_1, kappa_1, potential);

  matrix_sparse_vector_multiply_add(flow, m_hodge_1, dual_flow);
  free(dual_flow);
}
