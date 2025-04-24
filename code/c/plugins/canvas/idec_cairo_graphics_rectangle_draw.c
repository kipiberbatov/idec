#include <math.h>
#include <stdio.h>

#include "color.h"
#include "idec_cairo.h"
#include "idec_graphics_rectangle.h"
#include "idec_rgb.h"

/* must use get_color along with idec_rgb */
void idec_cairo_graphics_rectangle_draw(
  cairo_t * cr, int * status, const struct idec_graphics_rectangle * rectangle,
  void (*get_color)(struct idec_rgb *, const void *))
{
  double height, width, x, y;
  struct idec_rgb color;

  x = rectangle->x;
  y = rectangle->y;
  width = rectangle->width;
  height = rectangle->height;
  get_color(&color, rectangle->color);

  cairo_save(cr);
  cairo_set_source_rgb(cr, color.red, color.green, color.blue);
  cairo_rectangle(cr, x, y, width, height);
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
