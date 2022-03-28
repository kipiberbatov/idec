#ifndef QUASI_CUBE_PRIVATE_H
#define QUASI_CUBE_PRIVATE_H

#include "quasi_cube.h"

static const int r_triangulation_nodes_0[1] = {0};

static const int r_triangulation_nodes_1[2] = {0, 1};

static const int r_triangulation_nodes_2[6] = 
  {0, 1, 3,
   0, 2, 3};

static const int r_triangulation_nodes_3[24] = 
  {0, 1, 3, 7,
   0, 2, 3, 7,
   0, 1, 5, 7,
   0, 4, 5, 7,
   0, 2, 6, 7,
   0, 4, 6, 7};
   
void quasi_cube_triangulation_node_set(
  double * s_coord, const quasi_cube * r, int s_node, int r_node);

void quasi_cube_triangulation_simplex_set(
  double * s_coord, const quasi_cube * r, const int * r_nodes);

double quasi_cube_triangulation_simplex_measure(
  const quasi_cube * r, const int * r_nodes);

double quasi_cube_measure_from_triangulation(
  const quasi_cube * r, const int * r_nodes_all);

#endif /* QUASI_CUBE_PRIVATE_H */
