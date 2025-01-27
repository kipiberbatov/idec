#include <stdio.h>

#include "color.h"
#include "idec_cairo.h"
#include "idec_graphics_mesh_2d_edge.h"

void idec_cairo_graphics_mesh_2d_edge_black_draw(
  cairo_t * cr,
  int * status,
  const struct idec_graphics_mesh_2d_edge * edge)
{
  cairo_save(cr);
  cairo_set_source_rgb(cr, 0, 0, 0);
  cairo_set_line_width(cr, edge->width);
  cairo_move_to(cr, edge->e0[0], edge->e0[1]);
  cairo_line_to(cr, edge->e1[0], edge->e1[1]);
  cairo_stroke(cr);
  cairo_restore(cr);
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
