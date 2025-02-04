#include <stdlib.h>

#include "diffusion_transient_discrete_primal_strong.h"
#include "jagged.h"

void diffusion_transient_discrete_primal_strong_free(
  struct diffusion_transient_discrete_primal_strong * data)
{
  free(data->g_neumann);
  jagged1_free(data->boundary_neumann);
  free(data->g_dirichlet);
  jagged1_free(data->boundary_dirichlet);
  free(data->source);
  free(data->initial);
  free(data->kappa_1);
  free(data->pi_0);
  free(data);
}
