#ifndef _mesh_2d_colored_zero_cochain_h
#define _mesh_2d_colored_zero_cochain_h

#include <cairo.h>

#include "mesh.h"

typedef struct mesh_2d_colored_zero_cochain
{
  int number_of_nodes;
  int total_colors;
  double * coordinates;
  double * values;
  double point_size;
  double min_value;
  double max_value;
  void (*set_color)(cairo_t *, int *, int, int);
} mesh_2d_colored_zero_cochain;

void mesh_2d_colored_zero_cochain_cairo_draw(
  cairo_t * cr,
  int * status,
  const mesh_2d_colored_zero_cochain * c);

#endif /* mesh_2d_colored_zero_cochain */
