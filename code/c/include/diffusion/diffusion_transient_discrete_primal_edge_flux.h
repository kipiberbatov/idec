#include "mesh.h"

void diffusion_transient_discrete_primal_edge_flux(
  double * flux,
  const mesh * m,
  matrix_sparse * m_bd_1,
  const double * pi_1,
  int number_of_steps,
  const double * temperature);
