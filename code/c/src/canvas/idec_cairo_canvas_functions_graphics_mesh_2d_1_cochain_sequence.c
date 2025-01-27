#include <stdio.h>

#include "color.h"
#include "idec_animation_canvas_functions.h"
#include "idec_cairo.h"
#include "idec_graphics_mesh_2d_1_cochain_sequence.h"
#include "idec_graphics_mesh_2d_skeleton.h"

struct idec_animation_generic_data;

static void idec_cairo_draw_snapshot_graphics_mesh_2d_1_cochain_sequence(
  void * canvas,
  int * status,
  const void * data,
  const struct idec_animation_generic_data * generic_data,
  int total_colors,
  void (*set_color_cairo)(void *, int *, int, int))
{
  const struct idec_graphics_mesh_2d_1_cochain_sequence * cochain_sequence;
  struct idec_graphics_mesh_2d_skeleton skeleton;

  *(const void **) (&cochain_sequence) = data;
  skeleton.line_width = cochain_sequence->line_width;
  skeleton.coordinates = cochain_sequence->coordinates;
  skeleton.m = cochain_sequence->m;

  idec_graphics_mesh_2d_skeleton_draw(
    canvas,
    status,
    &skeleton,
    (void (*)(void *, int *, const struct idec_graphics_mesh_2d_edge *))
      idec_cairo_graphics_mesh_2d_edge_black_draw);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot draw skeleton\n", stderr);
    return;
  }

  idec_graphics_mesh_2d_1_cochain_sequence_draw_snapshot(
    canvas,
    status,
    cochain_sequence,
    generic_data,
    total_colors,
    set_color_cairo,
    (void (*)(void *, int *, const struct idec_graphics_mesh_2d_edge *))
      idec_cairo_graphics_mesh_2d_edge_perpendicular_oriented_draw);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot draw snapshot\n", stderr);
    return;
  }
}

/* This variable will be resolved at runtime by its name */
const struct idec_animation_canvas_functions
idec_cairo_canvas_functions_graphics_mesh_2d_1_cochain_sequence =
{
  (void (*)(void *, int *)) idec_cairo_paint_white,
  (void (*)(void *, int *, int, int)) idec_cairo_set_color_from_scheme_rainbow,
  idec_cairo_draw_snapshot_graphics_mesh_2d_1_cochain_sequence
};
