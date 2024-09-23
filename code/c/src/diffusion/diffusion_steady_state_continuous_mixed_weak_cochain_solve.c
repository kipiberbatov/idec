#include <errno.h>
#include <stdlib.h>

#include "diffusion_steady_state_continuous.h"
#include "diffusion_steady_state_discrete_mixed_weak.h"

void diffusion_steady_state_continuous_mixed_weak_cochain_solve(
  double * flux,
  double * temperature,
  const mesh * m,
  const matrix_sparse * m_cbd_dm1,
  const double * m_vol_dm1,
  const double * m_vol_d,
  const double * m_inner_dm1,
  const diffusion_steady_state_continuous * data_continuous)
{
  diffusion_steady_state_discrete_mixed_weak * data_discrete;

  data_discrete = diffusion_steady_state_discrete_mixed_weak_from_continuous(
    m, m_vol_dm1, m_vol_d, data_continuous);
  if (errno)
  {
    fprintf(stderr, "cannot discretize continuous data\n");
    return;
  }

  diffusion_steady_state_discrete_mixed_weak_solve(
    flux,
    temperature,
    m,
    m_cbd_dm1,
    m_inner_dm1,
    data_discrete);
  if (errno)
  {
    fprintf(stderr,
      "%s:%d: cannot solve discretized problem\n", __FILE__, __LINE__);
    goto data_discrete_free;
  }

data_discrete_free:
  diffusion_steady_state_discrete_mixed_weak_free(data_discrete);
}
