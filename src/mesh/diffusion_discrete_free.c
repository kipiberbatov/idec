#include <stdlib.h>

#include "diffusion_discrete.h"

void diffusion_discrete_free(diffusion_discrete * data)
{
  free(data->g_neumann);
  jagged1_free(data->boundary_neumann);
  free(data->g_dirichlet);
  jagged1_free(data->boundary_dirichlet);
  free(data->source);
  free(data->initial);
  free(data->pi_1);
  free(data->pi_0);
  free(data);
}
