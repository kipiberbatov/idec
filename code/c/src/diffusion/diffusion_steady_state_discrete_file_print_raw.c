#include "diffusion_steady_state_discrete.h"
#include "double_array.h"
#include "jagged.h"

void diffusion_steady_state_discrete_file_print_raw(
  FILE * out,
  const struct diffusion_steady_state_discrete * data)
{
  fprintf(out, "%d\n", data->number_of_cells_1);
  fprintf(out, "%d\n", data->number_of_cells_dm1);
  fprintf(out, "%d\n", data->number_of_cells_d);
  double_array_file_print(
    out, data->number_of_cells_dm1, data->conductivity, "--raw");
  double_array_file_print(
    out, data->number_of_cells_1, data->dual_conductivity, "--raw");
  double_array_file_print(
    out, data->number_of_cells_d, data->production_rate, "--raw");
  jagged1_file_print(out, data->boundary_dirichlet_dm1, "--raw");
  jagged1_file_print(out, data->boundary_dirichlet_0, "--raw");
  double_array_file_print(out,
    data->boundary_dirichlet_0->a0, data->g_dirichlet, "--raw");
  jagged1_file_print(out, data->boundary_neumann_dm1, "--raw");
  double_array_file_print(out,
    data->boundary_neumann_dm1->a0, data->g_neumann, "--raw");
}
