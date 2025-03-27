#include <math.h>
#include <stdio.h>

#include "color.h"
#include "idec_cairo.h"
#include "idec_graphics_mesh_2d_node.h"
#include "idec_rgb.h"

/* must use get_color along with idec_rgb */
void idec_cairo_graphics_mesh_2d_node_draw(
  cairo_t * cr, int * status, const struct idec_graphics_mesh_2d_node * node,
  void (*get_color)(void *, const void *))
{
  double r;
  double * x = node->coordinates;
  struct idec_rgb color;

  r = node->size;
  x = node->coordinates;
  get_color((void *) &color, node->color);

  cairo_save(cr);
  cairo_set_source_rgb(cr, color.red, color.green, color.blue);
  cairo_arc(cr, x[0], x[1], r, 0, 2 * M_PI);
  cairo_fill(cr);
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
