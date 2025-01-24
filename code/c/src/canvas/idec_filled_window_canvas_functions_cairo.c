#include <stdio.h>

#include <cairo.h>

#include "color.h"
#include "idec_animation_canvas_functions.h"
#include "idec_filled_window.h"
#include "idec_set_color_from_scheme_rainbow.h"

static void set_background_color_white(void * canvas)
{
  cairo_set_source_rgb((cairo_t *) canvas, 1, 1, 1);
}

static void draw_snapshot(
  void * canvas, int * status, const void * data, int total_colors,
  void (*set_color)(void *, int *, int, int))
{
  cairo_t * cr = (cairo_t *) canvas;
  struct idec_filled_window * object = (struct idec_filled_window *) data;

  set_color(canvas, status, object->new_index, object->total_colors);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot apply color set_color\n", stderr);
    return;
  }
  cairo_paint(cr);
}

/* This variable will be resolved at runtime by its address */
const struct idec_animation_canvas_functions
idec_filled_window_canvas_functions_cairo =
{
  set_background_color_white,
  (void (*)(void *, int *, int, int)) idec_set_color_from_scheme_rainbow,
  draw_snapshot
};
