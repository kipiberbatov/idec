#include <stdio.h>

#include "color.h"
#include "idec_animation_canvas_functions.h"
#include "idec_cairo.h"
#include "idec_graphics_mesh_2d_0_cochain_sequence.h"
#include "idec_graphics_mesh_2d_skeleton.h"

struct idec_animation_generic_data;

static void draw_snapshot_cairo(
  void * canvas,
  int * status,
  const void * data,
  const struct idec_animation_generic_data * generic_data,
  int total_colors,
  void (*set_color_cairo)(void *, int *, int, int))
{
  const struct idec_graphics_mesh_2d_0_cochain_sequence * cochain_sequence;
  struct idec_graphics_mesh_2d_skeleton skeleton;
  jagged2 cf_1_0;

  *(const void **) (&cochain_sequence) = data;
  skeleton.line_width = cochain_sequence->line_width;
  skeleton.coordinates = cochain_sequence->coordinates;
  mesh_cf_part2(&cf_1_0, cochain_sequence->m, 1, 0);
  skeleton.cf_1_0 = &cf_1_0;

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

  idec_graphics_mesh_2d_0_cochain_sequence_draw_snapshot(
    canvas,
    status,
    cochain_sequence,
    generic_data,
    total_colors,
    set_color_cairo,
    (void (*)(void *, int *, const struct idec_graphics_mesh_2d_node *))
      idec_cairo_graphics_mesh_2d_node_draw);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot draw snapshot\n", stderr);
    return;
  }
}

/* This variable will be resolved at runtime by its name */
const struct idec_animation_canvas_functions
idec_graphics_mesh_2d_0_cochain_sequence_canvas_functions_cairo =
{
  (void (*)(void *)) idec_cairo_paint_white,
  (void (*)(void *, int *, int, int)) idec_cairo_set_color_from_scheme_rainbow,
  draw_snapshot_cairo
};
