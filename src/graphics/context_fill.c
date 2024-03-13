#include "context_fill.h"
#include "rgb.h"

void context_fill(cairo_t * cr, double width, double height, int i, int n)
{
  rgb color;
  
  rgb_color(&color, i, n);
  cairo_set_source_rgb(cr, color.red, color.green, color.blue);
  cairo_set_line_width(cr, 1);
  cairo_rectangle(cr, 0, 0, width, height);
  cairo_fill(cr);
}
