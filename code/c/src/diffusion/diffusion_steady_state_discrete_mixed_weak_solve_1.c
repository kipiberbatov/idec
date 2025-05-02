#include "diffusion_steady_state_discrete.h"
#include "diffusion_steady_state_discrete_mixed_weak.h"
#include "diffusion_steady_state_discrete_mixed_weak_solve_1.h"

struct mesh;
struct matrix_sparse;

void diffusion_steady_state_discrete_mixed_weak_solve_1(
  double * flow_rate,
  double * dual_potential,
  const struct mesh * m,
  const struct matrix_sparse * m_cbd_dm1,
  const double * m_inner_dm1,
  const double * m_inner_d,
  const struct diffusion_steady_state_discrete * data)
{
  const struct diffusion_steady_state_discrete_mixed_weak data_1 =
  {
    data->number_of_cells_dm1,
    data->number_of_cells_d,
    data->conductivity,
    data->production_rate,
    data->boundary_dirichlet_dm1,
    data->boundary_dirichlet_0,
    data->g_dirichlet,
    data->boundary_neumann_dm1,
    data->g_neumann
  };

  diffusion_steady_state_discrete_mixed_weak_solve(flow_rate, dual_potential,
    m, m_cbd_dm1, m_inner_dm1, m_inner_d, &data_1);
}
