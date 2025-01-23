#include <stdio.h>

#include <cairo.h>

#include "color.h"
#include "idec_animation.h"
#include "idec_filled_window.h"
#include "paint_rgb.h"

static void set_background_color(void * canvas)
{
  cairo_set_source_rgb((cairo_t *) canvas, 1, 1, 1);
}

static void draw(
  void * canvas, int * status, const void * data, int total_colors,
  void (*scheme)(void *, int *, int, int))
{
  cairo_t * cr = (cairo_t *) canvas;
  struct idec_filled_window * object = (struct idec_filled_window *) data;

  scheme(canvas, status, object->new_index, object->total_colors);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot apply color scheme\n", stderr);
    return;
  }
  cairo_paint(cr);
}

const struct idec_animation_canvas_functions
idec_filled_window_canvas_functions_cairo =
{
  set_background_color,
  (void (*)(void *, int *, int, int)) paint_rgb,
  draw
};
