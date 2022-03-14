#ifndef QUASI_CUBE_H
#define QUASI_CUBE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct quasi_cube
{
  int dim_embedded;
  int dim;
  double * coord;
} quasi_cube;

void quasi_cube_set(
  quasi_cube * s, int s_dim_embedded, int s_dim, double * s_coord);

quasi_cube * quasi_cube_fscan(FILE * in);

void quasi_cube_free(quasi_cube * s);

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

double quasi_cube_measure(const quasi_cube * s);

void quasi_cube_centroid(double * s_medicenter, const quasi_cube * s);

#endif /* QUASI_CUBE_H */
