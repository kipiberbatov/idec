#include "diffusion_steady_state_discrete.h"
#include "diffusion_steady_state_discrete_free.h"
#include "idec_memory.h"
#include "jagged.h"

void diffusion_steady_state_discrete_free(
  struct diffusion_steady_state_discrete * data)
{
  idec_memory_free(data->g_neumann);
  jagged1_free(data->boundary_neumann_dm1);
  idec_memory_free(data->g_dirichlet);
  jagged1_free(data->boundary_dirichlet_0);
  jagged1_free(data->boundary_dirichlet_dm1);
  idec_memory_free(data->production_rate);
  idec_memory_free(data->dual_conductivity);
  idec_memory_free(data->conductivity);
  idec_memory_free(data);
}
