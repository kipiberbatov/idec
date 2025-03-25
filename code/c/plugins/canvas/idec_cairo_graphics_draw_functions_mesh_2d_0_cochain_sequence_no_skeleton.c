#include "idec_cairo.h"
#include "idec_graphics_mesh_2d_skeleton.h"
#include "idec_graphics_mesh_2d_0_cochain_sequence_draw_functions.h"

static void
do_nothing(void * cr, int * status, const struct idec_graphics_mesh_2d_edge * e)
{
}

static void (*draw_curves[1])(void *, int *, const void *) = 
{
  (void (*)(void *, int *, const void *)) idec_cairo_graphics_2d_segment_draw
};

const struct idec_graphics_mesh_2d_0_cochain_sequence_draw_functions
idec_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence_no_skeleton =
{
  (void (*)(void *, int *)) idec_cairo_paint_white,
  (void (*)(void *, int *, int, int)) idec_cairo_set_color_from_scheme_rainbow,
  (void (*)(void *, int *, const struct idec_graphics_mesh_2d_node *))
    idec_cairo_graphics_mesh_2d_node_draw,
  idec_graphics_mesh_2d_skeleton_draw,
  draw_curves,
  do_nothing
};
