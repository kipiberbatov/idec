#include <errno.h>
#include <stdlib.h>

#include "diffusion_steady_state_continuous.h"
#include "diffusion_steady_state_discrete_mixed_weak.h"

double * diffusion_steady_state_continuous_mixed_weak_cochain_solve(
  const mesh * m,
  const matrix_sparse * m_bd_d,
  const double * m_vol_dm1,
  const double * m_vol_d,
  const double * m_inner_dm1,
  const diffusion_steady_state_continuous * data_continuous)
{
  double * q, * result = NULL, * u;
  diffusion_steady_state_discrete_mixed_weak * data_discrete;

  data_discrete = diffusion_steady_state_discrete_mixed_weak_from_continuous(
    m, m_vol_dm1, m_vol_d, data_continuous);
  if (errno)
  {
    fprintf(stderr, "cannot discretize continuous data\n");
    goto end;
  }

  result = (double *) malloc(sizeof(double) * (m->cn[m->dim - 1] + m->cn[0]));
  if (errno)
  {
    fprintf(stderr, "cannot find discretized result\n");
    goto data_discrete_free;
  }
  
  q = result;
  u = result + m->cn[m->dim - 1];
  diffusion_steady_state_discrete_mixed_weak_solve(
    q,
    u,
    m,
    m_bd_d,
    m_inner_dm1,
    data_discrete);
  if (errno)
  {
    fprintf(stderr, "cannot find discretized result\n");
    free(result);
    goto data_discrete_free;
  }

data_discrete_free:
  diffusion_steady_state_discrete_mixed_weak_free(data_discrete);
end:
  return result;
}
