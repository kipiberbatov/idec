#include <stdlib.h>
#include "mesh.h"

void mesh_free(mesh * m)
{
  if (m->coord)
    free(m->coord);
  if (m->fc)
    jagged4_free(m->fc);
  if (m->cf)
    jagged4_free(m->cf);
  if (m->c)
    free(m->c);
  if (m->cn)
    free(m->cn);
  if (m)
    free(m);
}
