#include "mesh.h"

/* very hhacky solution for a particular problem */
void mesh_boundary_node_normal(double * normal, const mesh * m, int i)
{
  normal[0] = 0.;
  if (m->coord[m->dim_embedded * i + 1] == 0.)
    normal[1] = -1.;
  else
    normal[1] = 1.;
}
