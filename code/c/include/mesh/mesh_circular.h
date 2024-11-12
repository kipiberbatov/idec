#ifndef _mesh_circular_h
#define _mesh_circular_h

#include "mesh.h"

mesh * mesh_circular(int na, int nd, double radius, double x0, double y0);
void mesh_circular_boundary_values(double * m_boundary_values, int na, int nd);

#endif /* _mesh_circular_h */
