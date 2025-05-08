#ifndef _mesh_hemisphere_polar_h
#define _mesh_hemisphere_polar_h

#include "mesh.h"

void mesh_hemisphere_polar_coordinates(
  double * m_coord, int na, int nd, double radius,
  double x0, double y0, double z0);

mesh * mesh_hemisphere_polar(
  int na, int nd, double radius,
  double x0, double y0, double z0);

#endif /* _mesh_hemisphere_polar_h */
