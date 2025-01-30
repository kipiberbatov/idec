#include <stdio.h>

#include "color.h"
#include "idec_cairo.h"

void idec_cairo_paint_from_scheme(
  cairo_t * cr,
  int * status,
  int color_index,
  int total_colors,
  void (*set_color)(void *, int *, int, int))
{
  cairo_save(cr);
  set_color((void *) cr, status, color_index, total_colors);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot set color\n", stderr);
    return;
  }
  cairo_paint(cr);
  cairo_restore(cr);
  *status = cairo_status(cr);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot draw with Cairo: %s\n",
      cairo_status_to_string(*status));
    return;
  }
}
