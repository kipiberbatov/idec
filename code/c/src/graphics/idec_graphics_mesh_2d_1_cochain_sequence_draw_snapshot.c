#include <math.h>
#include <stdio.h>

#include "color.h"
#include "idec_animation_generic_data.h"
#include "idec_graphics_mesh_2d_1_cochain_sequence.h"
#include "idec_graphics_mesh_2d_edge.h"
#include "mesh.h"

static void edge_set_coordinates(
  struct idec_graphics_mesh_2d_edge * edge,
  const double * e0, const double * e1, double signed_value_ij)
{
  double v0, v1, v_norm, z0, z1;

  v0 = e1[1] - e0[1];
  v1 = e0[0] - e1[0];
  v_norm = sqrt(v0 * v0 + v1 * v1);
  v0 = (v0 / v_norm) * edge->width * 4;
  v1 = (v1 / v_norm) * edge->width * 4;
  z0 = (e0[0] + e1[0]) / 2;
  z1 = (e0[1] + e1[1]) / 2;

  if (signed_value_ij < 0)
  {
    edge->e0[0] = z0 - v0;
    edge->e0[1] = z1 - v1;
    edge->e1[0] = z0 + v0;
    edge->e1[1] = z1 + v1;
  }
  else
  {
    edge->e0[0] = z0 + v0;
    edge->e0[1] = z1 + v1;
    edge->e1[0] = z0 - v0;
    edge->e1[1] = z1 - v1;
  }
}

void idec_graphics_mesh_2d_1_cochain_sequence_draw_snapshot(
  void * canvas,
  int * status,
  const struct idec_graphics_mesh_2d_1_cochain_sequence * cochain_sequence,
  const struct idec_animation_generic_data * generic_data,
  int total_colors,
  void (*set_color)(void *, int *, int, int),
  void (*edge_draw)(void *, int *, const struct idec_graphics_mesh_2d_edge *))
{
  int i, j, number_of_edges;
  int * cf_1_0_a1, * cf_1_0_j;
  double color_coefficient, denominator, min, max, signed_value_ij;
  double * boundary_1, * coordinates, * e0_j, * e1_j, * values_i;
  struct jagged2 cf_1_0;
  struct idec_graphics_mesh_2d_edge edge;

  boundary_1 = cochain_sequence->boundary_1;
  coordinates = cochain_sequence->coordinates;
  min = cochain_sequence->min_value;
  max = cochain_sequence->max_value;
  denominator = max - min;

  edge.width = cochain_sequence->line_width;
  /* temporary hack to show flows on bad meshes */
  if (edge.width < 2.5)
    edge.width = 2.5;
  edge.total_colors = total_colors;
  edge.set_color = set_color;

  if (denominator == 0.)
    edge.color_index = 0;
  else
    color_coefficient = (double) (total_colors - 1) / denominator;

  mesh_cf_part2(&cf_1_0, cochain_sequence->m, 1, 0);
  number_of_edges = cf_1_0.a0;
  cf_1_0_a1 = cf_1_0.a1;
  cf_1_0_j = cf_1_0.a2;

  i = generic_data->new_index;
  values_i = cochain_sequence->values + number_of_edges * i;

  for (j = 0; j < number_of_edges; ++j)
  {
    if (denominator != 0.)
      edge.color_index = (int) ((fabs(values_i[j]) - min) * color_coefficient);
    signed_value_ij = boundary_1[2 * j] * values_i[j];
    e0_j = coordinates + 2 * cf_1_0_j[0];
    e1_j = coordinates + 2 * cf_1_0_j[1];
    edge_set_coordinates(&edge, e0_j, e1_j, signed_value_ij);
    edge_draw(canvas, status, &edge);
    if (*status)
    {
      color_error_position(__FILE__, __LINE__);
      fputs("cannot paint an edge\n", stderr);
      return;
    }
    cf_1_0_j += cf_1_0_a1[j];
  }
}
