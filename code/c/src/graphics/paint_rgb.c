#include <stdio.h>

#include "color.h"
#include "paint_rgb.h"
#include "rgb.h"

void paint_rgb(cairo_t * cr, int * status, int ind, int total_colors)
{
  rgb color;

  rgb_color(&color, status, ind, total_colors);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot set color\n", stderr);
    return;
  }

  cairo_set_source_rgb(cr, color.red, color.green, color.blue);
}
