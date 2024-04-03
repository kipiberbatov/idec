#include "mesh.h"

/* works only for a meshing of the unit square */
void mesh_boundary_node_normal(double * normal, const mesh * m, int i)
{
  double * x = m->coord + m->dim_embedded * i;

  if ((x[1] == 0. || x[1] == 1.) && x[0] != 0. && x[0] != 1.)
  {
    normal[0] = 0.;
    if (x[1] == 0.)
      normal[1] = -1.;
    else
      normal[1] = 1.;
  }
  else if ((x[0] == 0. || x[0] == 1.) && x[1] != 0. && x[1] != 0.)
  {
    normal[1] = 0.;
    if (x[0] == 0.)
      normal[0] = -1.;
    else
      normal[0] = 1.;
  }
}
