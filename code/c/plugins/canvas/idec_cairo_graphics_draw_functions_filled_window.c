#include <stdlib.h>

#include "idec_cairo.h"
#include "idec_rgb.h"
#include "idec_graphics_filled_window_draw_functions.h"

const struct idec_graphics_filled_window_draw_functions
idec_cairo_graphics_draw_functions_filled_window =
{
  (void (*)(void **, int *)) idec_rgb_allocate_color,
  free,
  (void (*)(void *, int *, int, int)) idec_rgb_set_from_scheme_rainbow,
  (void (*)(void *, int *, const void *)) idec_cairo_paint_rgb
};
