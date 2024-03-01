#ifndef MESH_BRICK_PRIVATE_H
#define MESH_BRICK_PRIVATE_H

#include "mesh_brick.h"

void mesh_brick_cn(int * m_cn, int m_dim, const int * n);

void mesh_brick_assign_n_bar(
  int * n_bar, int d, const int * n, int p, const int * a);

void mesh_brick_cf_a3(int * m_cf_a3, int m_dim, const int * m_cn);

void mesh_brick_cf_a4(int * m_cf_a4, int d, const int * n);

jagged4 * mesh_brick_cf(int m_dim, const int * m_cn, const int * n);

void mesh_brick_coord(double * m_coord, int m_dim, 
                      const double * brick_lengths, const int * n);

#endif /* MESH_BRICK_PRIVATE_H */
