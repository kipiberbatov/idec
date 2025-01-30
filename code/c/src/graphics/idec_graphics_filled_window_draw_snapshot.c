#include <stdio.h>

#include "color.h"
#include "idec_animation.h"
#include "idec_animation_generic_data.h"
#include "idec_graphics_filled_window_draw_functions.h"

void idec_graphics_filled_window_draw_snapshot(
  void * canvas,
  int * status,
  const struct idec_animation * animation)
{
  int color_index;
  const struct idec_graphics_filled_window_draw_functions * functions;

  color_index = animation->generic_data->new_index;
  *(const void **) (&functions) = animation->draw_functions;

  functions->paint(
    canvas,
    status,
    color_index,
    animation->total_colors,
    functions->set_color);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot set color %d\n", color_index);
    return;
  }
}
