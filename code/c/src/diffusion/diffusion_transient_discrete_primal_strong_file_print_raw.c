#include "diffusion_transient_discrete_primal_strong.h"
#include "double.h"

void diffusion_transient_discrete_primal_strong_file_print_raw(
  FILE * out,
  const diffusion_transient_discrete_primal_strong * data)
{
  fprintf(out, "%d\n", data->number_of_cells_0);
  fprintf(out, "%d\n", data->number_of_cells_1);
  double_array_file_print(out, data->number_of_cells_0, data->pi_0, "--raw");
  double_array_file_print(out, data->number_of_cells_1, data->pi_1, "--raw");
  double_array_file_print(out, data->number_of_cells_0, data->initial, "--raw");
  double_array_file_print(out, data->number_of_cells_0, data->source, "--raw");
  jagged1_file_print(out, data->boundary_dirichlet, "--raw");
  double_array_file_print(out,
    data->boundary_dirichlet->a0, data->g_dirichlet, "--raw");
  jagged1_file_print(out, data->boundary_neumann, "--raw");
  double_array_file_print(out,
    data->boundary_neumann->a0, data->g_neumann, "--raw");
}