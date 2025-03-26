#include "idec_cairo.h"
#include "idec_graphics_mesh_2d_skeleton.h"
#include "idec_graphics_mesh_2d_0_cochain_sequence.h"
#include "idec_graphics_mesh_2d_0_cochain_sequence_draw_functions.h"

static void (*draw_curves[2])(void *, int *, const void *) = 
{
  (void (*)(void *, int *, const void *)) idec_cairo_graphics_2d_segment_draw,
  (void (*)(void *, int *, const void *)) idec_cairo_graphics_2d_arc_draw
};

const struct idec_graphics_mesh_2d_0_cochain_sequence_draw_functions
idec_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence_circular_forman =
{
  (void (*)(void *, int *)) idec_cairo_paint_white,
  idec_graphics_mesh_2d_0_cochain_sequence_draw_values,
  (void (*)(void *, int *, int, int)) idec_cairo_set_color_from_scheme_rainbow,
  (void (*)(void *, int *, const struct idec_graphics_mesh_2d_node *))
    idec_cairo_graphics_mesh_2d_node_draw,
  idec_graphics_mesh_2d_skeleton_draw_circular_forman,
  draw_curves,
  (void (*)(void *, int *, const struct idec_graphics_mesh_2d_edge *))
    idec_cairo_graphics_mesh_2d_edge_black_draw
};
