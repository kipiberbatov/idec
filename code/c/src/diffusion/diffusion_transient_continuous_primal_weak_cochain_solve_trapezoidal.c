#include "diffusion_transient_continuous.h"
#include "diffusion_transient_discrete_primal_weak.h"

double *
diffusion_transient_continuous_primal_weak_cochain_solve_trapezoidal_method(
  const mesh * m,
  const double * m_vol_dm1,
  const double * m_vol_d,
  const double * m_inner_0,
  const double * m_inner_1,
  const diffusion_transient_continuous * data_continuous,
  double time_step,
  int number_of_steps)
{
  double * result = NULL;
  diffusion_transient_discrete_primal_weak * data_discrete;

  data_discrete = diffusion_transient_discrete_primal_weak_from_continuous(
    m, m_vol_dm1, m_vol_d, data_continuous);
  if (data_discrete == NULL)
  {
    fprintf(stderr,
      "%s:%d: cannot discretize continuous data\n", __FILE__, __LINE__);
    goto end;
  }

  result = diffusion_transient_discrete_primal_weak_solve_trapezoidal(
    m,
    m_inner_0,
    m_inner_1,
    data_discrete,
    time_step,
    number_of_steps
  );
  if (result == NULL)
  {
    fprintf(stderr,
      "%s:%d: cannot find discretized result\n", __FILE__, __LINE__);
    goto data_discrete_free;
  }

data_discrete_free:
  diffusion_transient_discrete_primal_weak_free(data_discrete);
end:
  return result;
}
