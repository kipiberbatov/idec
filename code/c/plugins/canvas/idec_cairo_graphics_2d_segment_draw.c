#include "idec_cairo.h"
#include "idec_graphics_2d_segment.h"

void idec_cairo_graphics_2d_segment_draw(
  cairo_t * cr, int * status, const struct idec_graphics_2d_segment * segment)
{
  cairo_move_to(cr, segment->x0[0], segment->x0[1]);
  cairo_line_to(cr, segment->x1[0], segment->x1[1]);
  cairo_stroke(cr);
}
