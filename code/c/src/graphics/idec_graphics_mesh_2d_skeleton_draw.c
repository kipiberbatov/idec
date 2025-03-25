#include <stdio.h>

#include "color.h"
#include "idec_graphics_2d_segment.h"
#include "idec_graphics_mesh_2d_edge.h"
#include "idec_graphics_mesh_2d_skeleton.h"
#include "mesh.h"

/* all edges are flat, embedded in 2D */
void idec_graphics_mesh_2d_skeleton_draw(
  void * canvas,
  int * status,
  const struct idec_graphics_mesh_2d_skeleton * skeleton,
  void (**draw_curves)(void *, int *, const void *),
  void (*draw_edge)(void *, int *, const struct idec_graphics_mesh_2d_edge *))
{
  int i, number_of_edges;
  int * cf_1_0_a1, * cf_1_0_i;
  double * coordinates, * x0, * x1;
  jagged2 cf_1_0;
  mesh * m;
  struct idec_graphics_mesh_2d_edge edge;
  struct idec_graphics_2d_segment segment;

  coordinates = skeleton->coordinates;
  edge.width = skeleton->line_width;
  edge.draw_curve = draw_curves[0];
  m = skeleton->m;
  mesh_cf_part2(&cf_1_0, m, 1, 0);
  number_of_edges = cf_1_0.a0;
  cf_1_0_i = cf_1_0.a2;
  cf_1_0_a1 = cf_1_0.a1;
  for (i = 0; i < number_of_edges; ++i)
  {
    x0 = coordinates + 2 * cf_1_0_i[0];
    x1 = coordinates + 2 * cf_1_0_i[1];
    segment.x0[0] = x0[0];
    segment.x0[1] = x0[1];
    segment.x1[0] = x1[0];
    segment.x1[1] = x1[1];
    edge.data = (void *) &segment;
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
