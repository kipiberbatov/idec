#include "mesh_2d_colored_one_cochain.h"

void mesh_2d_one_cochain_skeleton_draw(
  cairo_t * cr,
  int * status,
  const mesh_2d_colored_one_cochain * c)
{
  int c_number_of_edges, i;
  int * cf_1_0_a1, * cf_1_0_i;
  double width;
  double * c_coordinates, * e0, * e1;
  jagged2 * cf_1_0;

  c_coordinates = c->coordinates;
  width = c->line_width / 4;
  cf_1_0 = c->cf_1_0;
  c_number_of_edges = cf_1_0->a0;
  cf_1_0_i = cf_1_0->a2;
  cf_1_0_a1 = cf_1_0->a1;
  for (i = 0; i < c_number_of_edges; ++i)
  {
    e0 = c_coordinates + 2 * cf_1_0_i[0];
    e1 = c_coordinates + 2 * cf_1_0_i[1];
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, width);
    cairo_move_to(cr, e0[0], e0[1]);
    cairo_line_to(cr, e1[0], e1[1]);
    cairo_stroke(cr);
    cf_1_0_i += cf_1_0_a1[i];
  }
}
