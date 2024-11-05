#include "mesh_2d_colored_node.h"
#include "mesh_2d_colored_zero_cochain.h"

void mesh_2d_colored_zero_cochain_cairo_draw(
  cairo_t * cr,
  const mesh_2d_colored_zero_cochain * c)
{
  int c_number_of_nodes, j;
  double c_max, c_min, denominator;
  double * c_coordinates, * c_values;
  mesh_2d_colored_node node;

  c_min = c->min_value;
  c_max = c->max_value;
  c_number_of_nodes = c->number_of_nodes;
  c_coordinates = c->coordinates;
  c_values = c->values;
  node.size = c->point_size;
  node.total_colors = c->total_colors;
  node.paint = c->paint;
  denominator = c_max - c_min;
  for (j = 0; j < c_number_of_nodes; ++j)
  {
    node.coordinates = c_coordinates + 2 * j;
    if (denominator == 0.)
      node.relative_value = 0.;
    else
      node.relative_value = (c_values[j] - c_min) / denominator;
    // fprintf(stderr, "node.relative_value = %g\n", node.relative_value);
    mesh_2d_colored_node_cairo_draw(cr, &node);
  }
}
