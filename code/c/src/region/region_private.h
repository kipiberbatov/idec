#include "line_2d.h"
#include "point_2d.h"
#include "simplex.h"
#include "triangle_2d.h"
#include "quasi_cube.h"

#if 0
other types:
  QUAD,
  SQUARE,
  RECTANGLE,
  RHOMBUS,
  PARALLELOGRAM,
  PENTAGON,
  HEXAGON,
  POLYGON,
  REGULAR_POLYGON,
  /* 3D */
  TETRAHEDRON,
  PYRAMID,
  CUBE,
  PRISM,
  PARALLELEPIPED,
  HEXAHEDRON,
  /* nD */
  SIMPLEX,
  QUASI_CUBE,
  N_CUBE
#endif

typedef enum region_type
{
/* 2d */
  region_type_point_2d,
  region_type_line_2d,
  region_type_triangle_2d,
/* nD */
  region_type_simplex,
  region_type_quasi_cube
} region_type;

struct region
{
  region_type type;
  void * data;
};
