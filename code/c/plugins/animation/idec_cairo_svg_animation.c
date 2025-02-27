#include <stdio.h>

#include <cairo-svg.h>

#include "color.h"
#include "idec_cairo_animation_draw_to_file.h"

void idec_cairo_svg_animation(
  struct idec_animation * animation,
  int * status,
  int argc,
  char ** argv,
  const char * filename)
{
  if (filename == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("empty filenames are not allowed\n", stderr);
    *status = 1;
    return;
  }

  idec_cairo_animation_draw_to_file(
    animation, status, filename, cairo_svg_surface_create, NULL);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot draw animation to SVG file %s%s%s\n",
      color_variable, filename, color_none);
    return;
  }
}
