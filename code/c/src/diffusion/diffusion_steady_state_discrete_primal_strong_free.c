#include <stdlib.h>

#include "diffusion_steady_state_discrete_primal_strong.h"
#include "jagged.h"

void diffusion_steady_state_discrete_primal_strong_free(
  struct diffusion_steady_state_discrete_primal_strong * data)
{
  free(data->g_neumann);
  jagged1_free(data->boundary_neumann);
  free(data->g_dirichlet);
  jagged1_free(data->boundary_dirichlet);
  free(data->source);
  free(data->kappa_1);
  free(data);
}
