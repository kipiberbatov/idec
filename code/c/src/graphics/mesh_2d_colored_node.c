#include <math.h>

#include "mesh_2d_colored_node.h"

void mesh_2d_colored_node_cairo_draw(
  cairo_t * cr,
  int * status,
  const mesh_2d_colored_node * node)
{
  int ind;

  ind = (int) (node->relative_value * ((double) (node->total_colors - 1)));
  node->paint(cr, status, ind, node->total_colors);
  cairo_arc(cr, node->coordinates[0], node->coordinates[1],
    node->size, 0, 2 * M_PI);
  cairo_fill(cr);
  cairo_stroke(cr);
}
