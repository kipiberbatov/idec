#include <stdlib.h>
#include "simplex.h"

void simplex_free(simplex * s)
{
  free(s->coord);
  free(s);
}
