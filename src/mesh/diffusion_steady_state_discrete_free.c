#include <stdlib.h>

#include "diffusion_steady_state_discrete.h"

void
diffusion_steady_state_discrete_free(diffusion_steady_state_discrete * data)
{
  free(data->g_neumann);
  jagged1_free(data->boundary_neumann);
  free(data->g_dirichlet);
  jagged1_free(data->boundary_dirichlet);
  free(data->source);
  free(data->pi_1);
  free(data->pi_0);
  free(data);
}
