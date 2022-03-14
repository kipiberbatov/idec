#include "simplex.h"

void simplex_set(
  simplex * s, int s_dim_embedded, int s_dim, double * s_coord)
{
  s->dim_embedded = s_dim_embedded;
  s->dim = s_dim;
  s->coord = s_coord;
}
