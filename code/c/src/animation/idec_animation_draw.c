#include <stdio.h>

#include "color.h"
#include "idec_animation.h"
#include "idec_animation_canvas_functions.h"
#include "idec_animation_draw.h"

void idec_animation_draw(
  void * canvas,
  struct idec_animation * animation,
  int * status)
{
  animation->canvas_functions->set_background_color(canvas, status);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot set_background_color\n", stderr);
    return;
  }
  
  animation->canvas_functions->draw_snapshot(
    canvas,
    status,
    animation->data,
    animation->generic_data,
    animation->total_colors,
    animation->canvas_functions->set_color);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot draw snapshot\n", stderr);
    return;
  }
}
