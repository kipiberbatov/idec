#include "idec_cairo.h"
#include "idec_graphics_mesh_2d_1_cochain_sequence_draw_functions.h"

const struct idec_graphics_mesh_2d_1_cochain_sequence_draw_functions
idec_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence =
{
  (void (*)(void *, int *)) idec_cairo_paint_white,
  (void (*)(void *, int *, const struct idec_graphics_mesh_2d_edge *))
    idec_cairo_graphics_mesh_2d_edge_black_draw,
  (void (*)(void *, int *, int, int)) idec_cairo_set_color_from_scheme_rainbow,
  (void (*)(void *, int *, const struct idec_graphics_mesh_2d_edge *))
    idec_cairo_graphics_mesh_2d_edge_oriented_draw
};
