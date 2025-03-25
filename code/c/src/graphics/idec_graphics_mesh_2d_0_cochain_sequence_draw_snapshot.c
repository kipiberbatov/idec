#include <stdio.h>

#include "color.h"
#include "idec_animation.h"
#include "idec_graphics_mesh_2d_0_cochain_sequence.h"
#include "idec_graphics_mesh_2d_0_cochain_sequence_draw_functions.h"
#include "idec_graphics_mesh_2d_skeleton.h"

void idec_graphics_mesh_2d_0_cochain_sequence_draw_snapshot(
  void * canvas,
  int * status,
  const struct idec_animation * animation)
{
  struct idec_graphics_mesh_2d_0_cochain_sequence * cochain_sequence;
  struct idec_graphics_mesh_2d_skeleton skeleton;

  const struct idec_graphics_mesh_2d_0_cochain_sequence_draw_functions *
  functions;

  *(void **) (&cochain_sequence) = animation->data;
  *(const void **) (&functions) = animation->draw_functions;

  skeleton.line_width = cochain_sequence->line_width;
  skeleton.coordinates = cochain_sequence->coordinates;
  skeleton.m = cochain_sequence->m;

  functions->set_background_color(canvas, status);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot set set background color %d\n", stderr);
    return;
  }

  functions->draw_skeleton(
    canvas,
    status,
    &skeleton,
    functions->draw_curves,
    functions->draw_black_edge);
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
