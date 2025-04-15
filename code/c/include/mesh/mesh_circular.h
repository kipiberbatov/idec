#ifndef _mesh_circular_h
#define _mesh_circular_h

#include "mesh.h"

jagged4 * mesh_circular_cells_to_faces(int na, int nd, const int * m_cn);

void mesh_circular_only_topology(mesh * m, int na, int nd);

void mesh_circular_coordinates(
  double * m_coord, int na, int nd, double radius, double x0, double y0);

mesh * mesh_circular(int na, int nd, double radius, double x0, double y0);

void mesh_circular_boundary_values(double * m_boundary_values, int na, int nd);


#endif /* _mesh_circular_h */
