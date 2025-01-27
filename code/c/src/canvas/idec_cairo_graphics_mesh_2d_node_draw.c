#include <math.h>
#include <stdio.h>

#include "color.h"
#include "idec_cairo.h"
#include "idec_graphics_mesh_2d_node.h"

void idec_cairo_graphics_mesh_2d_node_draw(
  cairo_t * cr,
  int * status,
  const struct idec_graphics_mesh_2d_node * node)
{
  double * coordinates = node->coordinates;

  cairo_save(cr);
  node->set_color(cr, status, node->color_index, node->total_colors);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot set color\n", stderr);
    return;
  }
  cairo_arc(cr, coordinates[0], coordinates[1], node->size, 0, 2 * M_PI);
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
