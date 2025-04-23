#include "diffusion_transient_discrete_mixed_weak.h"
#include "double.h"
#include "jagged.h"

void diffusion_transient_discrete_mixed_weak_file_print_raw(
  FILE * out,
  const struct diffusion_transient_discrete_mixed_weak * data)
{
  fprintf(out, "%d\n", data->number_of_cells_dm1);
  fprintf(out, "%d\n", data->number_of_cells_d);
  double_array_file_print(out, data->number_of_cells_d, data->pi_d, "--raw");
  double_array_file_print(out,
    data->number_of_cells_dm1, data->kappa_dm1, "--raw");
  double_array_file_print(out,
    data->number_of_cells_d, data->initial_dual_potential, "--raw");
  double_array_file_print(out,
    data->number_of_cells_dm1, data->initial_flow_rate, "--raw");
  double_array_file_print(out, data->number_of_cells_d, data->source, "--raw");
  jagged1_file_print(out, data->boundary_dirichlet_dm1, "--raw");
  jagged1_file_print(out, data->boundary_dirichlet_0, "--raw");
  double_array_file_print(out,
    data->boundary_dirichlet_0->a0, data->g_dirichlet_0, "--raw");
  jagged1_file_print(out, data->boundary_neumann_dm1, "--raw");
  double_array_file_print(out,
    data->boundary_neumann_dm1->a0, data->g_neumann_dm1, "--raw");
}
