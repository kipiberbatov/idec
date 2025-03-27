#include <math.h>
#include <stdio.h>

#include "color.h"
#include "idec_cairo.h"
#include "idec_graphics_mesh_2d_edge.h"
#include "line_2d.h"

void idec_cairo_graphics_mesh_2d_edge_oriented_draw(
  cairo_t * cr, int * status, const struct idec_graphics_mesh_2d_edge * edge)
{
  struct line_2d * line = (struct line_2d *) edge->data;

  cairo_save(cr);
  cairo_set_line_width(cr, edge->width);
  cairo_move_to(cr, line->x0[0], line->x0[1]);
  cairo_line_to(cr, line->x1[0], line->x1[1]);
  cairo_stroke(cr);
  cairo_arc(cr, line->x1[0], line->x1[1], edge->width, 0, 2 * M_PI);
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
