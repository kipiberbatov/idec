#include <stdio.h>

#include "color.h"
#include "idec_cairo.h"
#include "idec_graphics_mesh_2d_edge.h"

void idec_cairo_graphics_mesh_2d_edge_black_draw(
  cairo_t * cr, int * status, const struct idec_graphics_mesh_2d_edge * edge,
  void (*draw_curve)(void *, int *, const void *))
{
  cairo_save(cr);
  cairo_set_source_rgb(cr, 0, 0, 0);
  cairo_set_line_width(cr, edge->width);
  draw_curve((void *) cr, status, edge->data);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot draw curve to Cairo context: %s\n",
      cairo_status_to_string(*status));
    return;
  }
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
