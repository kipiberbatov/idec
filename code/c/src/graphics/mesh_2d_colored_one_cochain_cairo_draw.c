#include "mesh_2d_colored_one_cochain.h"

void mesh_2d_colored_one_cochain_cairo_draw(
  cairo_t * cr,
  const mesh_2d_colored_one_cochain * c)
{
  c->draw_skeleton(cr, c);
  if (!(c->is_mesh_edge_skeleton))
    c->draw_values(cr, c);
}
