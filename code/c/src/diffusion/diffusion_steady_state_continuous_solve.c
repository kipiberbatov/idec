#include <errno.h>

#include "diffusion_steady_state_continuous.h"
#include "diffusion_steady_state_discrete.h"

#define FUNCTION "diffusion_steady_state_continuous_solve"
#define START_ERROR_MESSAGE fprintf(stderr,"  %s: ", FUNCTION)

double * diffusion_steady_state_continuous_solve(
  const mesh * m,
  const matrix_sparse * m_cbd_0,
  const matrix_sparse * m_cbd_star_1,
  const diffusion_steady_state_continuous * data_continuous)
{
  double * result = NULL;
  diffusion_steady_state_discrete * data_discrete;

  data_discrete =
  diffusion_steady_state_continuous_discretize(m, data_continuous);
  if (errno)
  {
    START_ERROR_MESSAGE;
    fprintf(stderr, "cannot discretize continuous data\n");
    goto end;
  }

  result = diffusion_steady_state_discrete_solve(
    m, m_cbd_0, m_cbd_star_1, data_discrete);
  if (errno)
  {
    START_ERROR_MESSAGE;
    fprintf(stderr, "cannot find discretized result\n");
    goto data_discrete_free;
  }

data_discrete_free:
  diffusion_steady_state_discrete_free(data_discrete);
end:
  return result;
}
