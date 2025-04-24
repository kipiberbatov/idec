#include <stdio.h>

#include "color.h"
#include "idec_animation.h"
#include "idec_animation_generic_data.h"
#include "idec_graphics_colorbar_direction.h"
#include "idec_graphics_colorbar_draw_functions.h"
#include "idec_graphics_rectangle.h"

void idec_graphics_colorbar_draw_snapshot(
  void * canvas,
  int * status,
  const struct idec_animation * animation)
{
  int total_colors;
  const struct idec_graphics_colorbar_draw_functions * functions;
  enum idec_graphics_colorbar_direction direction;
  struct idec_graphics_rectangle rectangle;

  total_colors = animation->total_colors;
  *(const void **) (&functions) = animation->draw_functions;
  direction = *(int *) animation->data;

  functions->check_color_scheme(status, total_colors);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot create color scheme with %s%d%s colors\n",
      color_variable, total_colors, color_none);
    return;
  }

  functions->allocate_color(&(rectangle.color), status);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot allocate color\n", stderr);
    return;
  }

  functions->draw_rectangles(
    &rectangle,
    canvas,
    status,
    animation->generic_data->width,
    animation->generic_data->height,
    direction,
    total_colors,
    functions);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot draw values %d\n", stderr);
    goto color_free;
  }

color_free:
  functions->deallocate_color(rectangle.color);
}
