#include "diffusion_steady_state_discrete.h"
#include "diffusion_steady_state_discrete_primal_weak.h"
#include "diffusion_steady_state_discrete_primal_weak_solve_1.h"
#include "idec_error_message.h"

struct mesh;

void diffusion_steady_state_discrete_primal_weak_solve_1(
  double ** potential,
  int * status,
  const struct mesh * m,
  const double * m_inner_1,
  const struct diffusion_steady_state_discrete * data)
{
  const struct diffusion_steady_state_discrete_primal_weak data_1 =
  {
    data->number_of_cells_1,
    data->number_of_cells_d,
    data->dual_conductivity,
    data->production_rate,
    data->boundary_dirichlet_0,
    data->g_dirichlet,
    data->boundary_neumann_dm1,
    data->g_neumann
  };

  *potential = diffusion_steady_state_discrete_primal_weak_solve(
    m, m_inner_1, &data_1);
  if (*potential == NULL)
  {
    idec_error_message_position_in_code(__FILE__, __LINE__);
    idec_error_message_cannot_calculate("potential");
    *status = 1;
    return;
  }
}
