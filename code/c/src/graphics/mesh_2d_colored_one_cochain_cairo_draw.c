#include "mesh_2d_colored_one_cochain.h"

void mesh_2d_colored_one_cochain_cairo_draw(
  cairo_t * cr,
  const mesh_2d_colored_one_cochain * c)
{
  mesh_2d_one_cochain_skeleton_draw(cr, c);
  if (!(c->is_mesh_edge_skeleton))
    mesh_2d_colored_one_cochain_values_cairo_draw(cr, c);
}
