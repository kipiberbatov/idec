#include <stdio.h>

#include "color.h"
#include "idec_set_color_from_scheme_rainbow.h"
#include "idec_rgb.h"

void idec_set_color_from_scheme_rainbow(
  cairo_t * cr, int * status, int ind, int total_colors)
{
  idec_rgb color;

  idec_rgb_set_from_scheme_rainbow(&color, status, ind, total_colors);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot set color\n", stderr);
    return;
  }

  cairo_set_source_rgb(cr, color.red, color.green, color.blue);
}
