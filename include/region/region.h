#ifndef REGION_H
#define REGION_H

#include "point.h"
#include "line.h"
#include "triangle.h"

typedef enum region_names_list
{
  /* 0D */
  POINT,
  /* 1D */
  LINE,
  /* 2D */
  TRIANGLE
  // QUAD,
  // SQUARE,
  // RECTANGLE,
  // RHOMBUS,
  // PARALLELOGRAM,
  // PENTAGON,
  // HEXAGON,
  // POLYGON,
  // REGULAR_POLYGON,
  // /* 3D */
  // TETRAHEDRON,
  // PYRAMID,
  // CUBE,
  // PRISM,
  // PARALLELEPIPED,
  // HEXAHEDRON,
  // /* nD */
  // SIMPLEX,
  // QUASI_CUBE,
  // N_CUBE
} region_names_list;

typedef struct region
{
  region_names_list name;
  void * object;
} region;

/***************************** memory_management ******************************/
region * region_new(region_names_list r_name, void * r_object);

void region_free(region * r);

/********************************* geometry ***********************************/
double region_measure(region * r);

#endif /* REGION_H */
