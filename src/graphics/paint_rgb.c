#include "paint_rgb.h"
#include "rgb.h"

void paint_rgb(cairo_t * cr, int ind, int total_colors)
{
  rgb color;
  
  rgb_color(&color, ind, total_colors);
  cairo_set_source_rgb(cr, color.red, color.green, color.blue);
}
