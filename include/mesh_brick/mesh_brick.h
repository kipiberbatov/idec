#ifndef MESH_BRICK_H
#define MESH_BRICK_H

#include "mesh.h"

int ** mesh_brick_bd(int d, const int * n, const int * m_bd_sizes);

mesh * mesh_brick(int d, const double * brick_lengths, const int * n);
mesh * mesh_brick_regular(int d, int n);

#endif /* MESH_BRICK_H */
