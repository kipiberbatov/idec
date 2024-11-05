#ifndef _mesh_2d_colored_edge_h
#define _mesh_2d_colored_edge_h

#include "mesh.h"
#include "painter.h"

typedef struct mesh_2d_colored_edge
{
  int total_colors;
  double coordinates_0[2];
  double coordinates_1[2];
  double point_size;
  double width;
  double relative_value;
  painter paint;
} mesh_2d_colored_edge;

void mesh_2d_colored_edge_cairo_draw(
  cairo_t * cr,
  const mesh_2d_colored_edge * edge);

#endif /* _mesh_2d_colored_edge_h */
