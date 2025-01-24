#include "idec_animation.h"
#include "idec_animation_canvas_functions.h"
#include "idec_animation_draw_snapshot.h"

void idec_animation_draw_snapshot(
  void * canvas,
  struct idec_animation * animation,
  int * status)
{
  animation->canvas_functions->draw_snapshot(
    canvas,
    status,
    animation->data,
    animation->generic_data,
    animation->total_colors,
    animation->canvas_functions->set_color);
}
