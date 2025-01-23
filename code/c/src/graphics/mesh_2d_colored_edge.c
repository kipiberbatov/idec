#include "color.h"
#include "mesh_2d_colored_edge.h"

#include <errno.h>
#include <math.h>

void mesh_2d_colored_edge_cairo_draw(
  cairo_t * cr,
  int * status,
  const mesh_2d_colored_edge * edge)
{
  int ind;

  ind = (int) (edge->relative_value * ((double) (edge->total_colors - 1)));
  edge->paint(cr, status, ind, edge->total_colors);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("painting is not possible\n", stderr);
    return;
  }
  cairo_set_line_width(cr, edge->width);
  cairo_move_to(cr, edge->coordinates_0[0], edge->coordinates_0[1]);
  cairo_line_to(cr, edge->coordinates_1[0], edge->coordinates_1[1]);
  cairo_stroke(cr);
  cairo_arc(cr, edge->coordinates_1[0], edge->coordinates_1[1],
    edge->point_size / 4, 0, 2 * M_PI);
  cairo_stroke(cr);
}
