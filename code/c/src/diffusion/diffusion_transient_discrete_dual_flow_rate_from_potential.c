#include "diffusion_steady_state_discrete_dual_flow_rate_from_potential.h"
#include "diffusion_transient_discrete_dual_flow_rate_from_potential.h"
#include "mesh.h"

void diffusion_transient_discrete_dual_flow_rate_from_potential(
  double * dual_flow_rate,
  const struct mesh * m,
  const struct matrix_sparse * m_bd_1,
  const double * kappa_1,
  int number_of_steps,
  const double * potential)
{
  int i, m_cn_0, m_cn_1;

  m_cn_0 = m->cn[0];
  m_cn_1 = m->cn[1];

  for (i = 0; i <= number_of_steps; ++i)
  {
    diffusion_steady_state_discrete_dual_flow_rate_from_potential(
      dual_flow_rate + m_cn_1 * i, m, m_bd_1, kappa_1, potential + m_cn_0 * i);
  }
}
