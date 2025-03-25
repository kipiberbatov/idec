#include "idec_cairo.h"
#include "idec_graphics_2d_arc.h"

void idec_cairo_graphics_2d_arc_draw(
  cairo_t * cr, int * status, const struct idec_graphics_2d_arc * arc)
{
  cairo_arc(cr, arc->x0, arc->y0, arc->r, arc->alpha, arc->beta);
  cairo_stroke(cr);
}
