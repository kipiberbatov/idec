#include <math.h>

#include "mesh_2d_colored_node.h"

void mesh_2d_colored_node_cairo_draw(
  cairo_t * cr,
  const mesh_2d_colored_node * node)
{
  int ind;

  ind = (int) (node->relative_value * ((double) (node->total_colors - 1)));
  // fprintf(stderr, "index = %d\n", ind);
  node->paint(cr, ind, node->total_colors);
  /* cairo_set_line_width(cr, 1);  */
  cairo_arc(cr, node->coordinates[0], node->coordinates[1],
    node->size, 0, 2 * M_PI);

  cairo_fill(cr);
  cairo_stroke(cr);
}
