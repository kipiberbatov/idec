#include "idec_cairo.h"
#include "idec_graphics_mesh_2d_skeleton.h"
#include "idec_graphics_mesh_2d_skeleton_draw_functions.h"

static void (*draw_curves[2])(void *, int *, const void *) = 
{
  (void (*)(void *, int *, const void *)) idec_cairo_graphics_2d_line_draw,
  (void (*)(void *, int *, const void *)) idec_cairo_graphics_2d_arc_draw
};

const struct idec_graphics_mesh_2d_skeleton_draw_functions
idec_cairo_graphics_draw_functions_mesh_2d_skeleton_circular =
{
  idec_graphics_mesh_2d_skeleton_draw_circular,
  draw_curves,
  (void (*)(void *, int *, const struct idec_graphics_mesh_2d_edge *))
    idec_cairo_graphics_mesh_2d_edge_black_draw
};
