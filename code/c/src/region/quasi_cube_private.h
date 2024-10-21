#ifndef _quasi_cube_private_h
#define _quasi_cube_private_h

#include "quasi_cube.h"

extern const int quasi_cube_triangulation_nodes_0[];

extern const int quasi_cube_triangulation_nodes_1[];

extern const int quasi_cube_triangulation_nodes_2[];

extern const int quasi_cube_triangulation_nodes_3[];

void quasi_cube_triangulation_node_set(
  double * s_coord, const quasi_cube * r, int s_node, int r_node);

void quasi_cube_triangulation_simplex_set(
  double * s_coord, const quasi_cube * r, const int * r_nodes);

double quasi_cube_triangulation_simplex_measure(
  const quasi_cube * r, const int * r_nodes);

double quasi_cube_measure_from_triangulation(
  const quasi_cube * r, const int * r_nodes_all);

#endif /* _quasi_cube_private_h */
