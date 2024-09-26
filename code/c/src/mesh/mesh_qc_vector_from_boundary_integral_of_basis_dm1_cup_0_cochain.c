#include <string.h>

#include "double.h"
#include "mesh_qc.h"

/*
calculate nonzero values of sparse vector g,
g_i := (c{d - 1, i} \_/ g_{gamma}^0)[gamma]
*/
void mesh_qc_vector_from_boundary_integral_of_basis_dm1_cup_0_cochain(
  double * g,
  const mesh * m,
  const jagged1 * boundary_hyperfaces,
  const double * coefficients_0)
{
  int dm1, size;
  double pow_2_dm1;

  dm1 = m->dim - 1;
  pow_2_dm1 = (double) (1 << dm1);
  size = boundary_hyperfaces->a0;
  memcpy(g, coefficients_0, sizeof(double) * size);
  double_array_multiply_with(g, size, 1 / pow_2_dm1);
}
