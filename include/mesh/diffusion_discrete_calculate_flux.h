#include "mesh.h"

double * diffusion_discrete_calculate_flux(
  const mesh * m,
  matrix_sparse * m_cbd,
  int number_of_steps,
  const double * temperature);
