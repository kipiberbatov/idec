#include <errno.h>

#include "diffusion_steady_state_continuous.h"
#include "diffusion_steady_state_discrete_primal_weak.h"

double * diffusion_steady_state_continuous_primal_weak_solve(
  const mesh * m,
  const double * m_vol_dm1,
  const double * m_vol_d,
  const double * m_inner_1,
  const diffusion_steady_state_continuous * data_continuous)
{
  double * result = NULL;
  diffusion_steady_state_discrete_primal_weak * data_discrete;

  data_discrete = diffusion_steady_state_discrete_primal_weak_from_continuous(
    m, m_vol_dm1, m_vol_d, data_continuous);
  if (errno)
  {
    fprintf(stderr, "cannot discretize continuous data\n");
    goto end;
  }

  result = diffusion_steady_state_discrete_primal_weak_solve(
    m, m_inner_1, data_discrete);
  if (errno)
  {
    fprintf(stderr, "cannot find discretized result\n");
    goto data_discrete_free;
  }

data_discrete_free:
  diffusion_steady_state_discrete_primal_weak_free(data_discrete);
end:
  return result;
}
