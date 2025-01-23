#include "color.h"
#include "mesh_2d_colored_one_cochain.h"

void mesh_2d_colored_one_cochain_values_cairo_draw(
  cairo_t * cr,
  int * status,
  const mesh_2d_colored_one_cochain * c)
{
  int c_number_of_edges, i;
  int * cf_1_0_a1, * cf_1_0_i;
  jagged2 * cf_1_0;
  mesh_2d_colored_edge edge;

  edge.point_size = c->point_size / 4;
  edge.width = c->line_width / 4;
  edge.total_colors = c->total_colors;
  edge.paint = c->paint;
  cf_1_0 = c->cf_1_0;
  c_number_of_edges = cf_1_0->a0;
  cf_1_0_i = cf_1_0->a2;
  cf_1_0_a1 = cf_1_0->a1;
  /* temporary hack to show flows on bad meshes */
  if (edge.width < 2.5)
  {
    edge.width = 2.5;
    edge.point_size = 5;
  }
  cf_1_0_i = cf_1_0->a2;
  for (i = 0; i < c_number_of_edges; ++i)
  {
    mesh_2d_colored_one_cochain_set_edge(&edge, c, i, cf_1_0_i);
    mesh_2d_colored_edge_cairo_draw(cr, status, &edge);
    if (*status)
    {
      color_error_position(__FILE__, __LINE__);
      fputs("cannot paint an edge\n", stderr);
      return;
    }
    cf_1_0_i += cf_1_0_a1[i];
  }
}
