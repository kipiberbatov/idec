#include <stdio.h>

#include "color.h"
#include "idec_graphics_rectangle.h"
#include "idec_graphics_colorbar_direction.h"
#include "idec_graphics_colorbar_draw_functions.h"
#include "idec_rgb.h"

void idec_graphics_colorbar_draw_values(
  void * canvas,
  int * status,
  double width,
  double height,
  enum idec_graphics_colorbar_direction direction,
  int total_colors,
  const struct idec_graphics_colorbar_draw_functions * functions)
{
  int j;
  double step_x, step_y;
  struct idec_graphics_rectangle rectangle;
  void (*set_color)(void *, int, int) = functions->set_color;
  void (*get_color)(void *, const void *) = functions->get_color;
  void (*draw_rectangle)(void *, int *, const struct idec_graphics_rectangle *,
    void (*)(void *, const void *)) = functions->draw_rectangle;

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

  step_x = width / (double) total_colors;
  step_y = height / (double) total_colors;
  rectangle.x = 0;

  if (direction == idec_graphics_colorbar_direction_horizontal)
  {
    rectangle.width = step_x;
    rectangle.height = height;
    rectangle.y = 0;
    for (j = 0; j < total_colors; ++j)
    {
      set_color(rectangle.color, j, total_colors);
      draw_rectangle(canvas, status, &rectangle, get_color);
      if (*status)
      {
        color_error_position(__FILE__, __LINE__);
        fputs("cannot draw rectangle\n", stderr);
        goto color_free;
      }
      rectangle.x += step_x;
    }
  }
  else /* direction == idec_graphics_colorbar_direction_vertical */
  {
    rectangle.width = width;
    rectangle.height = step_y;
    rectangle.y = height - step_y;
    for (j = 0; j < total_colors; ++j)
    {
      set_color(rectangle.color, j, total_colors);
      draw_rectangle(canvas, status, &rectangle, get_color);
      if (*status)
      {
        color_error_position(__FILE__, __LINE__);
        fputs("cannot draw rectangle\n", stderr);
        goto color_free;
      }
      rectangle.y -= step_y;
    }
  }

color_free:
  functions->deallocate_color(rectangle.color);
}
