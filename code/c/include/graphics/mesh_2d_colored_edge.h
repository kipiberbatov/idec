#ifndef _mesh_2d_colored_edge_h
#define _mesh_2d_colored_edge_h

#include <cairo.h>

#include "mesh.h"

typedef struct mesh_2d_colored_edge
{
  int total_colors;
  double coordinates_0[2];
  double coordinates_1[2];
  double point_size;
  double width;
  double relative_value;
  void (*set_color)(cairo_t *, int *, int, int);
} mesh_2d_colored_edge;

void mesh_2d_colored_edge_cairo_draw(
  cairo_t * cr,
  int * status,
  const mesh_2d_colored_edge * edge);

#endif /* _mesh_2d_colored_edge_h */
