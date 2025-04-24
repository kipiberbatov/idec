#include <stdlib.h>

#include "idec_cairo.h"
#include "idec_graphics_colorbar.h"
#include "idec_graphics_colorbar_draw_functions.h"
#include "idec_rgb.h"

struct idec_graphics_rectangle;

const struct idec_graphics_colorbar_draw_functions
idec_cairo_graphics_draw_functions_colorbar =
{
  (void (*)(void **, int *)) idec_rgb_allocate_color,
  free,
  idec_graphics_colorbar_draw_values,
  idec_rgb_check_color_scheme_rainbow,
  (void (*)(void *, int , int)) idec_rgb_set_from_scheme_rainbow_no_checks,
  (void (*)(void *, int *, const struct idec_graphics_rectangle *,
    void (*)(void *, const void *))) idec_cairo_graphics_rectangle_draw,
  (void (*)(void *, const void *)) idec_rgb_get_color_rgb
};
