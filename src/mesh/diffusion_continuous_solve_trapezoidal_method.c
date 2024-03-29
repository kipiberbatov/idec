#include <errno.h>

#include "diffusion_continuous.h"
#include "diffusion_discrete.h"

double ** diffusion_continuous_solve_trapezoidal_method(
  const mesh * m,
  const matrix_sparse * m_laplacian_0,
  const diffusion_continuous * data_continuous,
  double time_step,
  int number_of_steps)
{
  double ** result = NULL;
  diffusion_discrete * data_discrete;
  
  data_discrete = diffusion_continuous_discretize(m, data_continuous);
  if (errno)
  {
    fprintf(stderr, "Error - cannot do discrete calculations\n");
    goto end;
  }
  
  result = diffusion_discrete_solve_trapezoidal_method(
    m,
    m_laplacian_0,
    data_discrete,
    time_step,
    number_of_steps
  );
  if (errno)
  {
    fprintf(stderr, "Error - cannot solve system\n");
    goto data_discrete_free;
  }

data_discrete_free:
  diffusion_discrete_free(data_discrete);
end:
  return result;
}
