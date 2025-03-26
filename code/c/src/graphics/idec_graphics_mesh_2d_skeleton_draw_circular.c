#include <math.h>
#include <stdio.h>

#include "color.h"
#include "idec_graphics_2d_arc.h"
#include "idec_graphics_mesh_2d_edge.h"
#include "idec_graphics_mesh_2d_skeleton.h"
#include "line_2d.h"
#include "mesh.h"

void idec_graphics_mesh_2d_skeleton_draw_circular(
  void * canvas,
  int * status,
  const struct idec_graphics_mesh_2d_skeleton * skeleton,
  void (**draw_curves)(void *, int *, const void *),
  void (*draw_edge)(void *, int *, const struct idec_graphics_mesh_2d_edge *))
{
  int i, j, index, na, nd, product;
  int * cf_1_0_index, * m_cf_a3_2_0, * m_cn;
  double cx, cy, r, r0, rx, ry, theta;
  double * coordinates, * x0, * x1;
  jagged2 cf_1_0;
  mesh * m;
  struct idec_graphics_mesh_2d_edge edge;
  struct line_2d segment;
  struct idec_graphics_2d_arc arc;

  void (*draw_segment)(void *, int *, const void *) = draw_curves[0];
  void (*draw_arc)(void *, int *, const void *) = draw_curves[1];

  coordinates = skeleton->coordinates;
  edge.width = skeleton->line_width;
  m = skeleton->m;
  m_cn = m->cn;
  m_cf_a3_2_0 = m->cf->a3 + m_cn[1];
  mesh_cf_part2(&cf_1_0, m, 1, 0);
  cf_1_0_index = cf_1_0.a2;

  product = m_cn[2];
  na = 0;
  i = 0;
  while (m_cf_a3_2_0[i] == 3)
  {
    ++na;
    ++i;
  }
  nd = product / na;
  cx = coordinates[0];
  cy = coordinates[1];
  rx = coordinates[2 * m_cn[0] - 2] - cx;
  ry = coordinates[2 * m_cn[0] - 1] - cy;
  r = sqrt(rx * rx + ry * ry);
  r0 = r / nd;
  theta = M_PI * 2 / na;
  arc.x0 = cx;
  arc.y0 = cy;

  index = 0;
  for (i = 0; i < nd; ++i)
  {
    /* segments */
    edge.data = (void *) &segment;
    edge.draw_curve = draw_segment;
    for (j = 0; j < na; ++j)
    {
      x0 = coordinates + 2 * cf_1_0_index[0];
      x1 = coordinates + 2 * cf_1_0_index[1];
      segment.x0[0] = x0[0];
      segment.x0[1] = x0[1];
      segment.x1[0] = x1[0];
      segment.x1[1] = x1[1];
      draw_edge(canvas, status, &edge);
      if (*status)
      {
        color_error_position(__FILE__, __LINE__);
        fprintf(stderr, "cannot draw edge as a segment for index %d\n", index);
        return;
      }
      ++index;
      cf_1_0_index += 2;
    }

    /* arcs */
    edge.data = (void *) &arc;
    edge.draw_curve = draw_arc;
    arc.r = r0 * (i + 1);
    for (j = 0; j < na; ++j)
    {
      arc.alpha = j * theta;
      arc.beta = (j + 1) * theta;
      draw_edge(canvas, status, &edge);
      if (*status)
      {
        color_error_position(__FILE__, __LINE__);
        fprintf(stderr, "cannot draw edge as an arc for index %d\n", index);
        return;
      }
      ++index;
      cf_1_0_index += 2;
    }
  }
}
