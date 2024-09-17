#include <errno.h>

#include "diffusion_transient_continuous.h"
#include "diffusion_transient_discrete_primal_strong.h"

#define FUNCTION "diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal"
#define START_ERROR_MESSAGE fprintf(stderr,"  %s: ", FUNCTION)

double * diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal(
  const mesh * m,
  const matrix_sparse * m_cbd_0,
  const matrix_sparse * m_cbd_star_1,
  const diffusion_transient_continuous * data_continuous,
  double time_step,
  int number_of_steps)
{
  double * result = NULL;
  diffusion_transient_discrete_primal_strong * data_discrete;

  data_discrete = diffusion_transient_discrete_primal_strong_from_continuous(
    m, data_continuous);
  if (errno)
  {
    START_ERROR_MESSAGE;
    fprintf(stderr, "cannot discretize continuous data\n");
    goto end;
  }

  result = diffusion_transient_discrete_primal_strong_solve_trapezoidal(
    m,
    m_cbd_0,
    m_cbd_star_1,
    data_discrete,
    time_step,
    number_of_steps
  );
  if (errno)
  {
    START_ERROR_MESSAGE;
    fprintf(stderr, "cannot find discretized result\n");
    goto data_discrete_free;
  }

data_discrete_free:
  diffusion_transient_discrete_primal_strong_free(data_discrete);
end:
  return result;
}
