#include <stdlib.h>

#include "diffusion_transient_discrete_primal_weak.h"
#include "double.h"
#include "int.h"

diffusion_transient_discrete_primal_weak *
diffusion_transient_discrete_primal_weak_file_scan_raw(FILE * in)
{
  diffusion_transient_discrete_primal_weak * data;

  data = (diffusion_transient_discrete_primal_weak *) malloc(
    sizeof(diffusion_transient_discrete_primal_weak));

  data->number_of_cells_0 = int_file_scan(in);

  data->number_of_cells_1 = int_file_scan(in);

  data->number_of_cells_d = int_file_scan(in);

  data->pi_0 = double_array_file_scan(in, data->number_of_cells_0, "--raw");

  data->pi_1 = double_array_file_scan(in, data->number_of_cells_1, "--raw");

  data->initial = double_array_file_scan(in, data->number_of_cells_0, "--raw");

  data->source = double_array_file_scan(in, data->number_of_cells_d, "--raw");

  data->boundary_dirichlet = jagged1_file_scan(in, "--raw");

  data->g_dirichlet = double_array_file_scan(in,
    data->boundary_dirichlet->a0, "--raw");

  data->boundary_neumann = jagged1_file_scan(in, "--raw");

  data->g_neumann = double_array_file_scan(in,
    data->boundary_neumann->a0, "--raw");

  return data;
}