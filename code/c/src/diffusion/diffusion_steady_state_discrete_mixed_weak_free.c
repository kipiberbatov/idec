#include <stdlib.h>
#include "diffusion_steady_state_discrete_mixed_weak.h"

void diffusion_steady_state_discrete_mixed_weak_free(
  diffusion_steady_state_discrete_mixed_weak * data)
{
  free(data->g_neumann_dm1);
  jagged1_free(data->boundary_neumann_dm1);
  free(data->g_dirichlet_0);
  jagged1_free(data->boundary_dirichlet_0);
  jagged1_free(data->boundary_dirichlet_dm1);
  free(data->source_d);
  free(data->pi_dm1);
  free(data);
}
