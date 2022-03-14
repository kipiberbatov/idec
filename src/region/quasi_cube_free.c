#include "quasi_cube.h"

void quasi_cube_free(quasi_cube * s)
{
  free(s->coord);
  free(s);
}
