#include <stdlib.h>

#include "diffusion_transient_discrete_mixed_weak.h"
#include "jagged.h"

void diffusion_transient_discrete_mixed_weak_free(
  struct diffusion_transient_discrete_mixed_weak * data)
{
  free(data->g_neumann_dm1);
  jagged1_free(data->boundary_neumann_dm1);
  free(data->g_dirichlet_0);
  jagged1_free(data->boundary_dirichlet_0);
  jagged1_free(data->boundary_dirichlet_dm1);
  free(data->source);
  free(data->initial_flow_rate);
  free(data->initial_dual_potential);
  free(data->kappa_dm1);
  free(data->pi_d);
  free(data);
}
