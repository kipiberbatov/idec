#include "idec_animation.h"
#include "idec_animation_draw.h"

void idec_animation_draw(
  void * canvas,
  struct idec_animation * animation,
  int * status)
{
  animation->canvas_functions->draw(
    canvas,
    status,
    animation->data,
    animation->total_colors,
    animation->canvas_functions->color_scheme);
}
