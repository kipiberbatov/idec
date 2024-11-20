#include "diffusion_steady_state_discrete_primal_dual_flow.h"
#include "diffusion_transient_discrete_primal_dual_flow.h"

void diffusion_transient_discrete_primal_dual_flow(
  double * dual_flow,
  const mesh * m,
  const matrix_sparse * m_bd_1,
  const double * pi_1,
  int number_of_steps,
  const double * potential)
{
  int i, m_cn_0, m_cn_1;

  m_cn_0 = m->cn[0];
  m_cn_1 = m->cn[1];

  for (i = 0; i <= number_of_steps; ++i)
  {
    diffusion_steady_state_discrete_primal_dual_flow(
      dual_flow + m_cn_1 * i, m,  m_bd_1, pi_1, potential + m_cn_0 * i);
  }
}
