#include <stdio.h>

#include "color.h"
#include "idec_animation.h"
#include "idec_animation_generic_data.h"
#include "idec_graphics_colorbar_direction.h"
#include "idec_graphics_colorbar_draw_functions.h"

void idec_graphics_colorbar_draw_snapshot(
  void * canvas,
  int * status,
  const struct idec_animation * animation)
{
  const struct idec_graphics_colorbar_draw_functions * functions;
  enum idec_graphics_colorbar_direction direction;

  *(const void **) (&functions) = animation->draw_functions;
  direction = *(int *) animation->data;

  functions->draw_values(
    canvas,
    status,
    animation->generic_data->width,
    animation->generic_data->height,
    direction,
    animation->total_colors,
    functions);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot draw values %d\n", stderr);
    return;
  }
}
