#include "idec_cairo.h"
#include "idec_set_color_from_scheme_rainbow.h"

void idec_cairo_set_color_from_scheme_rainbow(
  cairo_t * cr, int * status, int color_index, int total_colors)
{
  idec_set_color_from_scheme_rainbow(cr, status, color_index, total_colors);
}
