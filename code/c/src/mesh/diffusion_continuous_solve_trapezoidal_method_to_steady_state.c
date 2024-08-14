#include <errno.h>

#include "diffusion_continuous.h"
#include "diffusion_discrete.h"

double_array_sequence_dynamic *
diffusion_continuous_solve_trapezoidal_method_to_steady_state(
  const mesh * m,
  const matrix_sparse * m_cbd_0,
  const matrix_sparse * m_cbd_star_1,
  const diffusion_continuous * data_continuous,
  double time_step,
  double tolerance)
{
  diffusion_discrete * data_discrete;
  double_array_sequence_dynamic * result = NULL;

  data_discrete = diffusion_continuous_discretize(m, data_continuous);
  if (errno)
  {
    fprintf(stderr, "Error - cannot do discrete calculations\n");
    goto end;
  }

  result = diffusion_discrete_solve_trapezoidal_method_to_steady_state(
    m,
    m_cbd_0,
    m_cbd_star_1,
    data_discrete,
    time_step,
    tolerance
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
