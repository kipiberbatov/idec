#include <stdio.h>

#include "color.h"
#include "idec_animation.h"
#include "idec_graphics_mesh_2d_skeleton.h"
#include "idec_graphics_mesh_2d_skeleton_draw_functions.h"

void idec_graphics_mesh_2d_skeleton_draw_snapshot(
  void * canvas,
  int * status,
  const struct idec_animation * animation)
{
  struct idec_graphics_mesh_2d_skeleton * skeleton;
  const struct idec_graphics_mesh_2d_skeleton_draw_functions * functions;

  *(void **) (&skeleton) = animation->data;
  *(const void **) (&functions) = animation->draw_functions;

  idec_graphics_mesh_2d_skeleton_draw(
    canvas,
    status,
    skeleton,
    functions->draw_edge);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot draw skeleton %d\n", stderr);
    return;
  }
}
