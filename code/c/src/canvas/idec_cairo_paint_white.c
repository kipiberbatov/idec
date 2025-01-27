#include "idec_cairo.h"

void idec_cairo_paint_white(cairo_t * cr)
{
  cairo_save(cr);
  cairo_set_source_rgb(cr, 1, 1, 1);
  cairo_paint(cr);
  cairo_restore(cr);
}
