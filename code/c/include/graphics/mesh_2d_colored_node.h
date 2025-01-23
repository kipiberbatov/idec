#ifndef _mesh_2d_colored_node_h
#define _mesh_2d_colored_node_h

#include <cairo.h>

#include "mesh.h"

typedef struct mesh_2d_colored_node
{
  int total_colors;
  double * coordinates;
  double size;
  double relative_value;
  void (*set_color)(cairo_t *, int *, int, int);
} mesh_2d_colored_node;

void mesh_2d_colored_node_cairo_draw(
  cairo_t * cr,
  int * status,
  const mesh_2d_colored_node * node);

#endif /* _mesh_2d_colored_node_h */
