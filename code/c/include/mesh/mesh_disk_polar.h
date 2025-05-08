#ifndef _mesh_disk_polar_h
#define _mesh_disk_polar_h

#include "mesh.h"

jagged4 * mesh_disk_polar_cells_to_faces(int na, int nd, const int * m_cn);

void mesh_disk_polar_only_topology(mesh * m, int na, int nd);

void mesh_disk_polar_coordinates(
  double * m_coord, int na, int nd, double radius, double x0, double y0);

mesh * mesh_disk_polar(int na, int nd, double radius, double x0, double y0);

void
mesh_disk_polar_boundary_values(double * m_boundary_values, int na, int nd);


#endif /* _mesh_disk_polar_h */
