#include <stdio.h>

#include <cairo.h>

#include "color.h"
#include "idec_animation_canvas_functions.h"
#include "idec_animation_generic_data.h"
#include "idec_set_color_from_scheme_rainbow.h"

static void set_background_color_white(void * canvas)
{
  cairo_set_source_rgb((cairo_t *) canvas, 1, 1, 1);
}

static void draw_snapshot(
  void * canvas,
  int * status,
  const void * data,
  const struct idec_animation_generic_data * generic_data,
  int total_colors,
  void (*set_color)(void *, int *, int, int))
{
  set_color(canvas, status, generic_data->new_index, total_colors);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot apply color set_color\n", stderr);
    return;
  }
  cairo_paint((cairo_t *) canvas);
}

/* This variable will be resolved at runtime by its address */
const struct idec_animation_canvas_functions
idec_filled_window_canvas_functions_cairo =
{
  set_background_color_white,
  (void (*)(void *, int *, int, int)) idec_set_color_from_scheme_rainbow,
  draw_snapshot
};
