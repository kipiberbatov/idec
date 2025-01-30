#include "idec_cairo.h"
#include "idec_graphics_mesh_2d_skeleton_draw_functions.h"

const struct idec_graphics_mesh_2d_skeleton_draw_functions
idec_cairo_graphics_draw_functions_mesh_2d_skeleton =
{
  (void (*)(void *, int *, const struct idec_graphics_mesh_2d_edge *))
    idec_cairo_graphics_mesh_2d_edge_black_draw
};
