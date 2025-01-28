#include <stdio.h>

#include "color.h"
#include "idec_animation_canvas_functions.h"
#include "idec_cairo.h"
#include "idec_graphics_mesh_2d_skeleton.h"

struct idec_animation_generic_data;

static void idec_cairo_draw_snapshot_graphics_mesh_2d_skeleton(
  void * canvas,
  int * status,
  const void * data,
  const struct idec_animation_generic_data * generic_data,
  int total_colors,
  void (*set_color)(void *, int *, int, int))
{
  idec_graphics_mesh_2d_skeleton_draw(
    canvas,
    status,
    (const struct idec_graphics_mesh_2d_skeleton *) data,
    (void (*)(void *, int *, const struct idec_graphics_mesh_2d_edge *))
      idec_cairo_graphics_mesh_2d_edge_black_draw);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot draw skeleton\n", stderr);
    return;
  }
}

/* This variable will be resolved at runtime by its name */
const struct idec_animation_canvas_functions
idec_cairo_canvas_functions_graphics_mesh_2d_skeleton =
{
  (void (*)(void *, int *)) idec_cairo_paint_white,
  NULL,
  idec_cairo_draw_snapshot_graphics_mesh_2d_skeleton
};
