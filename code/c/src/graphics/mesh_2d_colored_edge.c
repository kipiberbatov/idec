#include "mesh_2d_colored_edge.h"

void mesh_2d_colored_edge_cairo_draw(
  cairo_t * cr,
  const mesh_2d_colored_edge * edge)
{
  int ind;

  ind = (int) (edge->relative_value * ((double) (edge->total_colors - 1)));
  edge->paint(cr, ind, edge->total_colors);
  cairo_set_line_width(cr, edge->width);
  cairo_move_to(cr, edge->coordinates_0[0], edge->coordinates_0[1]);
  cairo_line_to(cr, edge->coordinates_1[0], edge->coordinates_1[1]);
  cairo_stroke(cr);
}
