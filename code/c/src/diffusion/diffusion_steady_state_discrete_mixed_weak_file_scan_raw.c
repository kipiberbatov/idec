#include <stdlib.h>

#include "diffusion_steady_state_discrete_mixed_weak.h"
#include "double_array.h"
#include "int.h"
#include "jagged.h"

struct diffusion_steady_state_discrete_mixed_weak *
diffusion_steady_state_discrete_mixed_weak_file_scan_raw(FILE * in)
{
  struct diffusion_steady_state_discrete_mixed_weak * data;

  *(void **) (&data) = malloc(sizeof(*data));

  data->number_of_cells_dm1 = int_file_scan(in);

  data->number_of_cells_d = int_file_scan(in);

  data->kappa_dm1 = double_array_file_scan(
    in, data->number_of_cells_dm1, "--raw");

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
