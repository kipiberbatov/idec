#include <stdio.h>

#include "color.h"
#include "idec_animation.h"
#include "idec_animation_intrinsic_functions.h"

void idec_animation_check_input(
  int * status, const struct idec_animation * animation)
{
  void * data;
  int initial_index, timelapse, total_steps;
  double height, width;
  const struct idec_animation_intrinsic_functions * intrinsic_functions;

  data = animation->data;
  intrinsic_functions = animation->intrinsic_functions;

  width = intrinsic_functions->get_width(data);
  if (width <= 0.)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "the width of the window is %s%g%s but it must be positive\n",
      color_variable, width, color_none);
    *status = 1;
    return;
  }

  height = intrinsic_functions->get_height(data);
  if (width <= 0.)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "the heigth of the window is %s%g%s but it must be positive\n",
      color_variable, height, color_none);
    *status = 1;
    return;
  }
  
  total_steps = intrinsic_functions->get_total_steps(data);
  if (total_steps <= 0)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "the total number of steps is %s%d%s but it must be positive\n",
      color_variable, total_steps, color_none);
    *status = 1;
    return;
  }
  
  initial_index = *(intrinsic_functions->get_new_index_address(data));
  if (initial_index < 0 || initial_index >= total_steps)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "the initial index is %s%d%s but it must be in the interval "
      "[0, total_steps) = [0, %s%d%s)\n",
      color_variable, initial_index, color_none,
      color_variable, total_steps, color_none);
    *status = 1;
    return;
  }

  timelapse = animation->timelapse;
  if (timelapse <= 0)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "timelapse = %s%d%s but it must be positive.\n",
      color_variable, timelapse, color_none);
    *status = 1;
    return;
  }
}
