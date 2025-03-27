#include <math.h>
#include <stdio.h>

#include "color.h"
#include "idec_cairo.h"
#include "idec_graphics_mesh_2d_edge.h"
#include "idec_rgb.h"
#include "line_2d.h"

void idec_cairo_graphics_mesh_2d_edge_oriented_draw(
  cairo_t * cr, int * status, const struct idec_graphics_mesh_2d_edge * edge,
  void (*get_color)(void *, const void *))
{
  double width;
  struct line_2d * line;
  struct idec_rgb color;

  width = edge->width;
  line = (struct line_2d *) edge->data;
  get_color((void *) &color, edge->color);

  cairo_save(cr);
  cairo_set_source_rgb(cr, color.red, color.green, color.blue);
  cairo_set_line_width(cr, width);
  cairo_move_to(cr, line->x0[0], line->x0[1]);
  cairo_line_to(cr, line->x1[0], line->x1[1]);
  cairo_stroke(cr);
  cairo_arc(cr, line->x1[0], line->x1[1], width, 0, 2 * M_PI);
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
