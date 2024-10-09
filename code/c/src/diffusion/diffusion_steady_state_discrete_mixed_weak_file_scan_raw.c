#include <stdlib.h>

#include "diffusion_steady_state_discrete_mixed_weak.h"
#include "double.h"

diffusion_steady_state_discrete_mixed_weak *
diffusion_steady_state_discrete_mixed_weak_file_scan_raw(FILE * in)
{
  diffusion_steady_state_discrete_mixed_weak * data;

  data = (diffusion_steady_state_discrete_mixed_weak *) malloc(
    sizeof(diffusion_steady_state_discrete_mixed_weak));

  data->number_of_cells_dm1 = double_file_scan(in);

  data->number_of_cells_d = double_file_scan(in);

  data->pi_dm1 = double_array_file_scan(in, data->number_of_cells_dm1, "--raw");

  data->source_d = double_array_file_scan(in, data->number_of_cells_d, "--raw");

  data->boundary_dirichlet_dm1 = jagged1_file_scan(in, "--raw");

  data->boundary_dirichlet_0 = jagged1_file_scan(in, "--raw");

  data->g_dirichlet_0 = double_array_file_scan(in,
    data->boundary_dirichlet_0->a0, "--raw");

  data->boundary_neumann_dm1 = jagged1_file_scan(in, "--raw");

  data->g_neumann_dm1 = double_array_file_scan(in,
    data->boundary_neumann_dm1->a0, "--raw");

  return data;
}
