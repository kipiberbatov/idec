#ifndef _mesh_2d_colored_one_cochain_h
#define _mesh_2d_colored_one_cochain_h

#include "mesh.h"
#include "painter.h"

typedef struct mesh_2d_colored_one_cochain
{
  int total_colors;
  jagged2 * cf_1_0;
  double * coordinates;
  double * values;
  double line_width;
  double min_value;
  double max_value;
  painter paint;
} mesh_2d_colored_one_cochain;

void mesh_2d_colored_one_cochain_cairo_draw(
  cairo_t * cr,
  const mesh_2d_colored_one_cochain * c);

#endif /* mesh_2d_colored_one_cochain */
