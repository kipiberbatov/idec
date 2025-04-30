#ifndef _mesh_parallelotope_grid_h
#define _mesh_parallelotope_grid_h

#include "mesh.h"

void mesh_parallelotope_grid_coordinates(
  double * x,
  int d,
  int n,
  const double * origin,
  const double * directions,
  const int * partitions);

mesh * mesh_parallelotope_grid(
  int d,
  int n,
  const double * origin,
  const double * directions,
  const int * partitions);

#endif /* _mesh_parallelotope_grid_h */
