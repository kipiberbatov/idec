#include <math.h>
#include <stdio.h>
#include <string.h>

#include "color.h"
#include "idec_graphics_mesh_2d_1_cochain_sequence.h"
#include "idec_graphics_mesh_2d_1_cochain_sequence_draw_functions.h"
#include "idec_graphics_mesh_2d_edge.h"
#include "line_2d.h"
#include "mesh.h"

void idec_graphics_mesh_2d_1_cochain_sequence_draw_values(
  void * canvas,
  int * status,
  const struct idec_graphics_mesh_2d_1_cochain_sequence * cochain_sequence,
  const struct idec_graphics_mesh_2d_1_cochain_sequence_draw_functions *
    functions,
  int i,
  int total_colors)
{
  int color_index, j, number_of_edges;
  int * cf_1_0_a1, * cf_1_0_j;
  double color_coefficient, denominator, min, max, sign, size;
  double * boundary_1, * coordinates, * values_i;
  struct jagged2 cf_1_0;
  struct idec_graphics_mesh_2d_edge edge;
  struct line_2d flow_rate_direction, line;
  void (*set_color)(void *, int, int) = functions->set_color;
  void (*get_color)(void *, const void *) = functions->get_color;
  void (*draw_oriented_edge)(void *, int *,
    const struct idec_graphics_mesh_2d_edge *,
    void (*)(void *, const void *)) = functions->draw_oriented_edge;

  min = cochain_sequence->min_value;
  max = cochain_sequence->max_value;
  denominator = max - min;
  if (denominator == 0.)
    return;
  color_coefficient = (double) (total_colors - 1) / denominator;

  boundary_1 = cochain_sequence->boundary_1;
  coordinates = cochain_sequence->coordinates;

  edge.width = cochain_sequence->line_width;
  if (edge.width < 2.5)
    edge.width = 2.5;

  mesh_cf_part2(&cf_1_0, cochain_sequence->m, 1, 0);
  number_of_edges = cf_1_0.a0;
  cf_1_0_a1 = cf_1_0.a1;
  cf_1_0_j = cf_1_0.a2;

  functions->check_color_scheme(status, total_colors);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot create color scheme with %d colors\n",
      total_colors);
    return;
  }

  functions->allocate_color(&(edge.color), status);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot allocate color\n", stderr);
    return;
  }

  size = edge.width * 8;
  edge.data = (void *) &flow_rate_direction;
  values_i = cochain_sequence->values + number_of_edges * i;
  for (j = 0; j < number_of_edges; ++j)
  {
    color_index = (int) ((fabs(values_i[j]) - min) * color_coefficient);
    if (color_index)
    {
      set_color(edge.color, color_index, total_colors);
      memcpy(line.x0, coordinates + 2 * cf_1_0_j[0], sizeof(double) * 2);
      memcpy(line.x1, coordinates + 2 * cf_1_0_j[1], sizeof(double) * 2);
      sign = boundary_1[2 * j + 1] * values_i[j] > 0 ? 1 : -1;
      line_2d_set_flow_rate_direction(&flow_rate_direction, &line, sign, size);
      draw_oriented_edge(canvas, status, &edge, get_color);
      if (*status)
      {
        color_error_position(__FILE__, __LINE__);
        fputs("cannot paint an edge\n", stderr);
        goto color_free;
      }
    }
    cf_1_0_j += cf_1_0_a1[j];
  }
color_free:
  functions->deallocate_color(edge.color);
}
