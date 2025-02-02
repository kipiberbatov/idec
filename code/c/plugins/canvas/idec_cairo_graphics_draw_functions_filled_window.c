#include "idec_cairo.h"
#include "idec_graphics_filled_window_draw_functions.h"

const struct idec_graphics_filled_window_draw_functions
idec_cairo_graphics_draw_functions_filled_window =
{
  (void (*)(void *, int *, int, int)) idec_cairo_set_color_from_scheme_rainbow,
  (void (*)(void *, int *, int, int, void (*)(void *, int *, int, int)))
    idec_cairo_paint_from_scheme
};
