#include <stdio.h>

#include "color.h"
#include "idec_cairo.h"
#include "idec_rgb.h"

void idec_cairo_set_source_rgb(
  cairo_t * cr, int * status, const struct idec_rgb * color)
{
  cairo_set_source_rgb(cr, color->red, color->green, color->blue);
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
