#include "mesh_2d_colored_edge.h"
#include "mesh_2d_colored_one_cochain.h"

void mesh_2d_colored_one_cochain_cairo_draw(
  cairo_t * cr,
  const mesh_2d_colored_one_cochain * c)
{
  int c_number_of_edges, i;
  double c_max, c_min, denominator;
  double * c_coordinates, * c_values;
  mesh_2d_colored_edge edge;
  jagged1 cf_1_0_i;
  jagged2 * cf_1_0;
  
  c_min = c->min_value;
  c_max = c->max_value;
  c_coordinates = c->coordinates;
  c_values = c->values;
  edge.width = c->line_width;
  edge.total_colors = c->total_colors;
  edge.paint = c->paint;
  denominator = c_max - c_min;
  cf_1_0 = c->cf_1_0;
  c_number_of_edges = cf_1_0->a0;
  for (i = 0; i < c_number_of_edges; ++i)
  {
    jagged2_part1(&cf_1_0_i, cf_1_0, i);
    edge.coordinates_0 = c_coordinates + 2 * cf_1_0_i.a1[0];
    edge.coordinates_1 = c_coordinates + 2 * cf_1_0_i.a1[1];
    edge.relative_value = (c_values[i] - c_min) / denominator;
    mesh_2d_colored_edge_cairo_draw(cr, &edge);
  }
}
