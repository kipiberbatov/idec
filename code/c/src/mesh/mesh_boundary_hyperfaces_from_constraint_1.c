#include "mesh.h"

void mesh_boundary_hyperfaces_from_constraint_1(
  struct jagged1 ** result,
  int * status,
  const struct mesh * m,
  const struct jagged1 * m_boundary_dm1,
  int (*constraint)(const double *))
{
  *result = mesh_boundary_hyperfaces_from_constraint(m, constraint);
  if (*result == NULL)
  {
    *status = 1;
    return;
  }
}
