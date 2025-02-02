#include <stdio.h>

#include "color.h"
#include "idec_animation.h"
#include "idec_graphics_mesh_2d_0_cochain_sequence.h"
#include "idec_graphics_mesh_2d_0_cochain_sequence_draw_functions.h"

void idec_graphics_mesh_2d_0_cochain_sequence_draw_snapshot(
  void * canvas,
  int * status,
  const struct idec_animation * animation)
{
  struct idec_graphics_mesh_2d_0_cochain_sequence * cochain_sequence;

  const struct idec_graphics_mesh_2d_0_cochain_sequence_draw_functions *
  functions;

  *(void **) (&cochain_sequence) = animation->data;
  *(const void **) (&functions) = animation->draw_functions;

  functions->set_background_color(canvas, status);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot set set background color %d\n", stderr);
    return;
  }

  idec_graphics_mesh_2d_0_cochain_sequence_draw_skeleton(
    canvas, status, cochain_sequence, functions->draw_black_edge);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot draw skeleton %d\n", stderr);
    return;
  }

  idec_graphics_mesh_2d_0_cochain_sequence_draw_values(
    canvas, status, cochain_sequence, animation->generic_data,
    animation->total_colors, functions->set_color, functions->draw_node);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot draw values %d\n", stderr);
    return;
  }
}
