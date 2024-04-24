#ifndef _mesh_brick_h
#define _mesh_brick_h

#include "mesh.h"

int ** mesh_brick_boundary(int d, const int * n, const int * m_bd_sizes);

mesh * mesh_brick(int d, const double * brick_lengths, const int * n);
mesh * mesh_brick_regular(int d, int n);

#endif /* _mesh_brick_h */
