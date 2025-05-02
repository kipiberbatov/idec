#include <errno.h>

#include "diffusion_steady_state_discrete.h"
#include "diffusion_steady_state_discrete_file_scan_raw.h"
#include "double_array.h"
#include "idec_error_message.h"
#include "idec_memory.h"
#include "int.h"
#include "jagged.h"

void diffusion_steady_state_discrete_file_scan_raw(
  FILE * in,
  struct diffusion_steady_state_discrete ** result,
  int * status)
{
  struct diffusion_steady_state_discrete * data;

  idec_memory_allocate((void **) result, status, sizeof(**result));
  if (*status)
  {
    idec_error_message_position_in_code(__FILE__, __LINE__);
    idec_error_message_memory_allocate("result");
    return;
  }

  data = *result;

  data->number_of_cells_1 = int_file_scan(in);
  if (errno)
  {
    idec_error_message_position_in_code(__FILE__, __LINE__);
    idec_error_message_cannot_calculate("data->number_of_cells_1");
    *status = errno;
    goto end;
  }

  data->number_of_cells_dm1 = int_file_scan(in);
  if (errno)
  {
    idec_error_message_position_in_code(__FILE__, __LINE__);
    idec_error_message_cannot_calculate("data->number_of_cells_dm1");
    *status = errno;
    goto end;
  }

  data->number_of_cells_d = int_file_scan(in);
  if (errno)
  {
    idec_error_message_position_in_code(__FILE__, __LINE__);
    idec_error_message_cannot_calculate("data->number_of_cells_d");
    *status = errno;
    goto end;
  }

  data->conductivity = double_array_file_scan(
    in, data->number_of_cells_dm1, "--raw");
  if (data->conductivity == NULL)
  {
    idec_error_message_position_in_code(__FILE__, __LINE__);
    idec_error_message_cannot_calculate("data->conductivity");
    *status = errno;
    goto end;
  }

  data->dual_conductivity = double_array_file_scan(
    in, data->number_of_cells_1, "--raw");
  if (data->dual_conductivity == NULL)
  {
    idec_error_message_position_in_code(__FILE__, __LINE__);
    idec_error_message_cannot_calculate("data->dual_conductivity");
    *status = errno;
    goto conductivity_free;
  }

  data->production_rate = double_array_file_scan(in,
    data->number_of_cells_d, "--raw");
  if (data->production_rate == NULL)
  {
    idec_error_message_position_in_code(__FILE__, __LINE__);
    idec_error_message_cannot_calculate("data->production_rate");
    *status = errno;
    goto dual_conductivity_free;
  }

  data->boundary_dirichlet_dm1 = jagged1_file_scan(in, "--raw");
  if (data->boundary_dirichlet_dm1 == NULL)
  {
    idec_error_message_position_in_code(__FILE__, __LINE__);
    idec_error_message_cannot_calculate("data->boundary_dirichlet_dm1");
    *status = errno;
    goto production_rate_free;
  }

  data->boundary_dirichlet_0 = jagged1_file_scan(in, "--raw");
  if (data->boundary_dirichlet_0 == NULL)
  {
    idec_error_message_position_in_code(__FILE__, __LINE__);
    idec_error_message_cannot_calculate("data->boundary_dirichlet_0");
    *status = errno;
    goto boundary_dirichlet_dm1_free;
  }

  data->g_dirichlet = double_array_file_scan(in,
    data->boundary_dirichlet_0->a0, "--raw");
  if (data->g_dirichlet == NULL)
  {
    idec_error_message_position_in_code(__FILE__, __LINE__);
    idec_error_message_cannot_calculate("data->g_dirichlet");
    *status = errno;
    goto boundary_dirichlet_0_free;
  }

  data->boundary_neumann_dm1 = jagged1_file_scan(in, "--raw");
  if (data->boundary_neumann_dm1 == NULL)
  {
    idec_error_message_position_in_code(__FILE__, __LINE__);
    idec_error_message_cannot_calculate("data->boundary_neumann_dm1");
    *status = errno;
    goto g_dirichlet_free;
  }

  data->g_neumann = double_array_file_scan(in,
    data->boundary_neumann_dm1->a0, "--raw");
  if (data->g_neumann == NULL)
  {
    idec_error_message_position_in_code(__FILE__, __LINE__);
    idec_error_message_cannot_calculate("data->g_neumann");
    *status = errno;
    goto boundary_neumann_dm1_free;
  }

  *result = data;

  return;

  /* cleaning if an error occurs */
boundary_neumann_dm1_free:
  jagged1_free(data->boundary_neumann_dm1);
g_dirichlet_free:
  idec_memory_free(data->g_dirichlet);
boundary_dirichlet_0_free:
  jagged1_free(data->boundary_dirichlet_0);
boundary_dirichlet_dm1_free:
  jagged1_free(data->boundary_dirichlet_dm1);
production_rate_free:
  idec_memory_free(data->production_rate);
dual_conductivity_free:
  idec_memory_free(data->dual_conductivity);
conductivity_free:
  idec_memory_free(data->conductivity);
end:
  return;
}
