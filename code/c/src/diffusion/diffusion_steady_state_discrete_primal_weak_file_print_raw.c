#include "diffusion_steady_state_discrete_primal_weak.h"
#include "double.h"

void diffusion_steady_state_discrete_primal_weak_file_print_raw(
  FILE * out,
  const diffusion_steady_state_discrete_primal_weak * data)
{
  fprintf(out, "%d\n", data->number_of_cells_1);
  fprintf(out, "%d\n", data->number_of_cells_d);
  double_array_file_print(out, data->number_of_cells_1, data->pi_1, "--raw");
  double_array_file_print(out, data->number_of_cells_d, data->source, "--raw");
  jagged1_file_print(out, data->boundary_dirichlet, "--raw");
  double_array_file_print(out,
    data->boundary_dirichlet->a0, data->g_dirichlet, "--raw");
  jagged1_file_print(out, data->boundary_neumann, "--raw");
  double_array_file_print(out,
    data->boundary_neumann->a0, data->g_neumann, "--raw");
}
