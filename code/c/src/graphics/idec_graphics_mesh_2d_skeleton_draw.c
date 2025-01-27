#include <stdio.h>

#include "color.h"
#include "idec_graphics_mesh_2d_edge.h"
#include "idec_graphics_mesh_2d_skeleton.h"
#include "mesh.h"

void idec_graphics_mesh_2d_skeleton_draw(
  void * canvas,
  int * status,
  const struct idec_graphics_mesh_2d_skeleton * skeleton,
  void (*draw_edge)(void *, int *, const struct idec_graphics_mesh_2d_edge *))
{
  int i, number_of_edges;
  int * cf_1_0_a1, * cf_1_0_i;
  double * coordinates;
  jagged2 cf_1_0;
  mesh * m;
  struct idec_graphics_mesh_2d_edge edge;

  coordinates = skeleton->coordinates;
  edge.width = skeleton->line_width;
  m = skeleton->m;
  mesh_cf_part2(&cf_1_0, m, 1, 0);
  number_of_edges = cf_1_0.a0;
  cf_1_0_i = cf_1_0.a2;
  cf_1_0_a1 = cf_1_0.a1;
  for (i = 0; i < number_of_edges; ++i)
  {
    edge.e0 = coordinates + 2 * cf_1_0_i[0];
    edge.e1 = coordinates + 2 * cf_1_0_i[1];
    draw_edge(canvas, status, &edge);
    if (*status)
    {
      color_error_position(__FILE__, __LINE__);
      fprintf(stderr, "cannot draw edge %d\n", i);
      return;
    }
    cf_1_0_i += cf_1_0_a1[i];
  }
}
