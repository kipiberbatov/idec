#include <errno.h>

#include "color.h"
#include "diffusion_steady_state_discrete_primal_flow_from_potential.h"
#include "diffusion_transient_discrete_primal_flow_from_potential.h"

void diffusion_transient_discrete_primal_flow_from_potential(
  double * flow,
  const mesh * m,
  const matrix_sparse * m_bd_1,
  const double * pi_1,
  const double * potential,
  const matrix_sparse * m_hodge_1,
  int number_of_steps)
{
  int i, m_cn_1;

  m_cn_1 = m->cn[1];
  for (i = 0; i <= number_of_steps; ++i)
  {
    diffusion_steady_state_discrete_primal_flow_from_potential(
      flow + m_cn_1 * i, m, m_bd_1, pi_1, potential + m_cn_1 * i, m_hodge_1);
    if (errno)
    {
      color_error_position(__FILE__, __LINE__);
      fprintf(stderr, "cannot find flow[%d]\n", i);
      return;
    }
  }
}
