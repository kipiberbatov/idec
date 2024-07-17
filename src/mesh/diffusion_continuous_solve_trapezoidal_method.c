#include <errno.h>

#include "diffusion_continuous.h"
#include "diffusion_discrete.h"

#define FUNCTION "diffusion_continuous_solve_trapezoidal_method"
#define START_ERROR_MESSAGE fprintf(stderr,"  %s: ", FUNCTION)

double * diffusion_continuous_solve_trapezoidal_method(
  const mesh * m,
  const matrix_sparse * m_cbd_0,
  const matrix_sparse * m_cbd_star_1,
  const diffusion_continuous * data_continuous,
  double time_step,
  int number_of_steps)
{
  double * result = NULL;
  diffusion_discrete * data_discrete;
  
  data_discrete = diffusion_continuous_discretize(m, data_continuous);
  if (errno)
  {
    START_ERROR_MESSAGE;
    fprintf(stderr, "cannot discretize continuous data\n");
    goto end;
  }
  
  result = diffusion_discrete_solve_trapezoidal_method(
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
  diffusion_discrete_free(data_discrete);
end:
  return result;
}
