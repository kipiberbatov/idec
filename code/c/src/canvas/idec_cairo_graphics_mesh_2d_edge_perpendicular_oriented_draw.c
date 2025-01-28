#include <math.h>
#include <stdio.h>

#include "color.h"
#include "idec_cairo.h"
#include "idec_graphics_mesh_2d_edge.h"

void idec_cairo_graphics_mesh_2d_edge_perpendicular_oriented_draw(
  cairo_t * cr, int * status, const struct idec_graphics_mesh_2d_edge * edge)
{
  if (edge->color_index == 0)
    return;
  edge->set_color((void *) cr, status, edge->color_index, edge->total_colors);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("painting is not possible\n", stderr);
    return;
  }
  cairo_set_line_width(cr, edge->width);
  cairo_move_to(cr, edge->e0[0], edge->e0[1]);
  cairo_line_to(cr, edge->e1[0], edge->e1[1]);
  cairo_stroke(cr);
  cairo_arc(cr, edge->e1[0], edge->e1[1], edge->width, 0, 2 * M_PI);
  cairo_stroke(cr);
  *status = cairo_status(cr);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot render with Cairo: %s\n",
      cairo_status_to_string(*status));
    return;
  }
}
