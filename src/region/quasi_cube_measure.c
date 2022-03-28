#include "quasi_cube_private.h"

double quasi_cube_measure(const quasi_cube * r)
{
  int r_dim;
  
  r_dim = r->dim;
  switch (r_dim)
  {
  case 0:
    return 1;
  case 1:
    return quasi_cube_measure_from_triangulation(r, r_triangulation_nodes_1);
  case 2:
    return quasi_cube_measure_from_triangulation(r, r_triangulation_nodes_2);
  case 3:
    return quasi_cube_measure_from_triangulation(r, r_triangulation_nodes_3);
  default:
    return 0.;
  }
}
