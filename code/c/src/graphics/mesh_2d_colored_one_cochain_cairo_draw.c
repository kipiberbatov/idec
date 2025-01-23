#include "color.h"
#include "mesh_2d_colored_one_cochain.h"

void mesh_2d_colored_one_cochain_cairo_draw(
  cairo_t * cr,
  int * status,
  const mesh_2d_colored_one_cochain * c)
{
  c->draw_skeleton(cr, status, c);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot draw edge skeleton\n", stderr);
    return;
  }

  if (!(c->is_mesh_edge_skeleton))
  {
    c->draw_values(cr, status, c);
    if (*status)
    {
      color_error_position(__FILE__, __LINE__);
      fputs("cannot draw cochain values\n", stderr);
      return;
    }
  }
}
