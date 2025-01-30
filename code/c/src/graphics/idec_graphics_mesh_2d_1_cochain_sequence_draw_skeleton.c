#include <stdio.h>

#include "color.h"
#include "idec_graphics_mesh_2d_1_cochain_sequence.h"
#include "idec_graphics_mesh_2d_skeleton.h"

void idec_graphics_mesh_2d_1_cochain_sequence_draw_skeleton(
  void * canvas,
  int * status,
  const struct idec_graphics_mesh_2d_1_cochain_sequence * cochain_sequence,
  void (*edge_draw)(void *, int *, const struct idec_graphics_mesh_2d_edge *))
{
  struct idec_graphics_mesh_2d_skeleton skeleton;

  skeleton.line_width = cochain_sequence->line_width;
  skeleton.coordinates = cochain_sequence->coordinates;
  skeleton.m = cochain_sequence->m;
  idec_graphics_mesh_2d_skeleton_draw(canvas, status, &skeleton, edge_draw);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot draw skeleton\n", stderr);
    return;
  }
}
