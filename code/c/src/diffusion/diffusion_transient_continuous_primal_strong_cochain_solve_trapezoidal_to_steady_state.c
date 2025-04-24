#include "diffusion_transient_continuous.h"
#include "diffusion_transient_discrete_primal_strong.h"
#include "double_array_sequence_dynamic.h"
#include "mesh.h"

double_array_sequence_dynamic *
diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal_to_steady_state(
  const struct mesh * m,
  const struct matrix_sparse * m_cbd_0,
  const struct matrix_sparse * m_cbd_star_1,
  const struct diffusion_transient_continuous * data_continuous,
  double time_step,
  double tolerance)
{
  struct diffusion_transient_discrete_primal_strong * data_discrete;
  struct double_array_sequence_dynamic * result = NULL;

  data_discrete = diffusion_transient_discrete_primal_strong_from_continuous(
    m, data_continuous);
  if (data_discrete == NULL)
  {
    fprintf(stderr,
      "%s:%d: cannot discretize continuous data\n", __FILE__, __LINE__);
    goto end;
  }

  result =
  diffusion_transient_discrete_primal_strong_solve_trapezoidal_to_steady_state(
    m, m_cbd_0, m_cbd_star_1, data_discrete, time_step, tolerance);
  if (result == NULL)
  {
    fprintf(stderr,
      "%s:%d: cannot solve discrete problem\n", __FILE__, __LINE__);
    goto data_discrete_free;
  }

data_discrete_free:
  diffusion_transient_discrete_primal_strong_free(data_discrete);
end:
  return result;
}
