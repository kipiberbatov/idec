#include <math.h>
#include <stdio.h>

#include "color.h"
#include "idec_graphics_2d_arc.h"
#include "idec_graphics_2d_segment.h"
#include "idec_graphics_mesh_2d_edge.h"
#include "idec_graphics_mesh_2d_skeleton.h"
#include "mesh.h"

void idec_graphics_mesh_2d_skeleton_draw_circular_forman(
  void * canvas,
  int * status,
  const struct idec_graphics_mesh_2d_skeleton * skeleton,
  void (**draw_curves)(void *, int *, const void *),
  void (*draw_edge)(void *, int *, const struct idec_graphics_mesh_2d_edge *))
{
  int end_index, i, j, index, na, nd;
  int * cf_1_0_index, * m_cn;
  double cx, cy, r, r0, rx, ry, theta;
  double * coordinates, * x0, * x1;
  jagged2 cf_1_0;
  mesh * m;
  struct idec_graphics_mesh_2d_edge edge;
  struct idec_graphics_2d_segment segment;
  struct idec_graphics_2d_arc arc;

  void (*draw_segment)(void *, int *, const void *) = draw_curves[0];
  void (*draw_arc)(void *, int *, const void *) = draw_curves[1];

  coordinates = skeleton->coordinates;
  edge.width = skeleton->line_width;
  m = skeleton->m;
  m_cn = m->cn;
  mesh_cf_part2(&cf_1_0, m, 1, 0);
  cf_1_0_index = cf_1_0.a2;

  na = 2 * (2 * m_cn[0] - m_cn[1] - 2);
  nd = (m_cn[0] - 1) / na;
  end_index = na * nd / 4;
  cx = coordinates[0];
  cy = coordinates[1];
  rx = coordinates[2 * end_index] - cx;
  ry = coordinates[2 * end_index + 1] - cy;
  r = sqrt(rx * rx + ry * ry);
  r0 = r / nd;
  theta = M_PI * 2 / na;
  arc.x0 = cx;
  arc.y0 = cy;

  index = 0;
  for (i = 1; i <= nd / 2; ++i)
  {
    /* rays */
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
    arc.r = r0 * 2 * i;
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

  /* inner circle: arc-ray-arc */
  arc.r = r0;
  for (j = 0; j < na / 2; ++j)
  {
    arc.alpha = 2 * j * theta;
    arc.beta = (2 * j + 1) * theta;
    edge.data = (void *) &arc;
    edge.draw_curve = draw_arc;
    draw_edge(canvas, status, &edge);
    if (*status)
    {
      color_error_position(__FILE__, __LINE__);
      fprintf(stderr, "cannot draw edge as an arc for index %d\n", index);
      return;
    }
    ++index;
    cf_1_0_index += 2;

    x0 = coordinates + 2 * cf_1_0_index[0];
    x1 = coordinates + 2 * cf_1_0_index[1];
    segment.x0[0] = x0[0];
    segment.x0[1] = x0[1];
    segment.x1[0] = x1[0];
    segment.x1[1] = x1[1];
    edge.data = (void *) &segment;
    edge.draw_curve = draw_segment;
    draw_edge(canvas, status, &edge);
    if (*status)
    {
      color_error_position(__FILE__, __LINE__);
      fprintf(stderr, "cannot draw edge as a segment for index %d\n", index);
      return;
    }
    ++index;
    cf_1_0_index += 2;

    arc.alpha = (2 * j + 1) * theta;
    arc.beta = (2 * j + 2) * theta;
    edge.data = (void *) &arc;
    edge.draw_curve = draw_arc;
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

  /* outer circles: ray-arc-ray-arc */
  for (i = 1; i < nd / 2; ++i)
  {
    arc.r = r0 * (2 * i + 1);
    for (j = 0; j < na / 2; ++j)
    {
      x0 = coordinates + 2 * cf_1_0_index[0];
      x1 = coordinates + 2 * cf_1_0_index[1];
      segment.x0[0] = x0[0];
      segment.x0[1] = x0[1];
      segment.x1[0] = x1[0];
      segment.x1[1] = x1[1];
      edge.data = (void *) &segment;
      edge.draw_curve = draw_segment;
      draw_edge(canvas, status, &edge);
      if (*status)
      {
        color_error_position(__FILE__, __LINE__);
        fprintf(stderr, "cannot draw edge as a segment for index %d\n", index);
        return;
      }
      ++index;
      cf_1_0_index += 2;

      arc.alpha = 2 * j * theta;
      arc.beta = (2 * j + 1) * theta;
      edge.data = (void *) &arc;
      edge.draw_curve = draw_arc;
      draw_edge(canvas, status, &edge);
      if (*status)
      {
        color_error_position(__FILE__, __LINE__);
        fprintf(stderr, "cannot draw edge as an arc for index %d\n", index);
        return;
      }
      ++index;
      cf_1_0_index += 2;

      x0 = coordinates + 2 * cf_1_0_index[0];
      x1 = coordinates + 2 * cf_1_0_index[1];
      segment.x0[0] = x0[0];
      segment.x0[1] = x0[1];
      segment.x1[0] = x1[0];
      segment.x1[1] = x1[1];
      edge.data = (void *) &segment;
      edge.draw_curve = draw_segment;
      draw_edge(canvas, status, &edge);
      if (*status)
      {
        color_error_position(__FILE__, __LINE__);
        fprintf(stderr, "cannot draw edge as a segment for index %d\n", index);
        return;
      }
      ++index;
      cf_1_0_index += 2;

      arc.alpha = (2 * j + 1) * theta;
      arc.beta = (2 * j + 2) * theta;
      edge.data = (void *) &arc;
      edge.draw_curve = draw_arc;
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
