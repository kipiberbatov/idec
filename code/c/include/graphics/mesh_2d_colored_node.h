#ifndef _mesh_2d_colored_node_h
#define _mesh_2d_colored_node_h

#include "mesh.h"
#include "painter.h"

typedef struct mesh_2d_colored_node
{
  int total_colors;
  double * coordinates;
  double size;
  double relative_value;
  painter paint;
} mesh_2d_colored_node;

void mesh_2d_colored_node_cairo_draw(
  cairo_t * cr,
  int * status,
  const mesh_2d_colored_node * node);

#endif /* _mesh_2d_colored_node_h */
