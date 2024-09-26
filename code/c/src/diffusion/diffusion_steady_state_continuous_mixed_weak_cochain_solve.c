#include <errno.h>
#include <stdlib.h>

#include "color.h"
#include "diffusion_steady_state_continuous.h"
#include "diffusion_steady_state_discrete_mixed_weak.h"

void diffusion_steady_state_continuous_mixed_weak_cochain_solve(
  double * flux,
  double * temperature,
  const mesh * m,
  const matrix_sparse * m_bd_d,
  const double * m_vol_dm1,
  const double * m_vol_d,
  const double * m_inner_dm1,
  const double * m_inner_d,
  const diffusion_steady_state_continuous * data_continuous)
{
  diffusion_steady_state_discrete_mixed_weak * data_discrete;

  data_discrete = diffusion_steady_state_discrete_mixed_weak_from_continuous(
    m, m_vol_dm1, m_vol_d, data_continuous);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot discretize continuous data\n", stderr);
    return;
  }

  diffusion_steady_state_discrete_mixed_weak_solve(
    flux,
    temperature,
    m,
    m_bd_d,
    m_inner_dm1,
    m_inner_d,
    data_discrete);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot solve discretized problem\n", stderr);
    goto data_discrete_free;
  }

data_discrete_free:
  diffusion_steady_state_discrete_mixed_weak_free(data_discrete);
}
