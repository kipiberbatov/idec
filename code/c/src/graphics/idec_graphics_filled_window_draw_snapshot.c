#include <stdio.h>

#include "color.h"
#include "idec_animation.h"
#include "idec_animation_generic_data.h"
#include "idec_graphics_filled_window.h"
#include "idec_graphics_filled_window_draw_functions.h"

void idec_graphics_filled_window_draw_snapshot(
  void * canvas,
  int * status,
  const struct idec_animation * animation)
{
  int color_index, total_colors;
  struct idec_graphics_filled_window filled_window;
  const struct idec_graphics_filled_window_draw_functions * functions;

  *(void **) (&filled_window) = animation->data;

  color_index = animation->generic_data->new_index;
  total_colors = animation->total_colors;
  *(const void **) (&functions) = animation->draw_functions;

  functions->allocate_color(&(filled_window.color), status);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot allocate color\n", stderr);
    return;
  }

  functions->set_color(filled_window.color, status, color_index, total_colors);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot set color %d\n", color_index);
    goto color_free;
  }

  functions->paint(canvas, status, filled_window.color);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot set color %d\n", color_index);
    goto color_free;
  }

color_free:
  functions->deallocate_color(filled_window.color);
}
