#include "idec_cairo.h"
#include "idec_graphics_mesh_2d_skeleton.h"
#include "idec_graphics_mesh_2d_1_cochain_sequence.h"
#include "idec_graphics_mesh_2d_1_cochain_sequence_draw_functions.h"

static void (*draw_curves[1])(void *, int *, const void *) = 
{
  (void (*)(void *, int *, const void *)) idec_cairo_graphics_2d_segment_draw
};

const struct idec_graphics_mesh_2d_1_cochain_sequence_draw_functions
idec_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence =
{
  (void (*)(void *, int *)) idec_cairo_paint_white,
  idec_graphics_mesh_2d_1_cochain_sequence_draw_values,
  (void (*)(void *, int *, int, int)) idec_cairo_set_color_from_scheme_rainbow,
  (void (*)(void *, int *, const struct idec_graphics_mesh_2d_edge *))
    idec_cairo_graphics_mesh_2d_edge_oriented_draw,
  idec_graphics_mesh_2d_skeleton_draw,
  draw_curves,
  (void (*)(void *, int *, const struct idec_graphics_mesh_2d_edge *))
    idec_cairo_graphics_mesh_2d_edge_black_draw
};
