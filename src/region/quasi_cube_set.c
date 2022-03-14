#include "quasi_cube.h"

void quasi_cube_set(
  quasi_cube * s, int s_dim_embedded, int s_dim, double * s_coord)
{
  s->dim_embedded = s_dim_embedded;
  s->dim = s_dim;
  s->coord = s_coord;
}
