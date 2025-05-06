#include "boundary_scalar_field_discretize.h"
#include "de_rham.h"

void de_rham_boundary_0(
  double * x,
  const struct mesh * m,
  const struct jagged1 * boundary,
  double (*f)(const double *))
{
  boundary_scalar_field_discretize(x, m->dim_embedded, m->coord, boundary, f);
}
