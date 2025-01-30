#include <stdio.h>

#include "color.h"
#include "idec_animation_generic_data.h"
#include "idec_graphics_mesh_2d_0_cochain_sequence.h"
#include "idec_graphics_mesh_2d_node.h"

void idec_graphics_mesh_2d_0_cochain_sequence_draw_values(
  void * canvas,
  int * status,
  const struct idec_graphics_mesh_2d_0_cochain_sequence * cochain_sequence,
  const struct idec_animation_generic_data * generic_data,
  int total_colors,
  void (*set_color)(void *, int *, int, int),
  void (*draw_node)(void *, int *, const struct idec_graphics_mesh_2d_node *))
{
  int i, j, number_of_nodes;
  double color_coefficient, max, min, denominator;
  double * coordinates, * point_sizes, * values_i;
  struct idec_graphics_mesh_2d_node node;

  min = cochain_sequence->min_value;
  max = cochain_sequence->max_value;
  number_of_nodes = cochain_sequence->m->cn[0];
  node.total_colors = total_colors;
  node.set_color = set_color;
  denominator = max - min;
  point_sizes = cochain_sequence->point_sizes;
  coordinates = cochain_sequence->coordinates;

  i = generic_data->new_index;
  values_i = cochain_sequence->values + number_of_nodes * i;
  if (denominator == 0.)
  {
    node.color_index = 0.;
    for (j = 0; j < number_of_nodes; ++j)
    {
      node.size = point_sizes[j];
      node.coordinates = coordinates + 2 * j;
      draw_node(canvas, status, &node);
      if (*status)
      {
        color_error_position(__FILE__, __LINE__);
        fputs("cannot draw node\n", stderr);
        return;
      }
    }
  }
  else
  {
    color_coefficient = (double) (total_colors - 1) / denominator;
    for (j = 0; j < number_of_nodes; ++j)
    {
      node.color_index = (int) ((values_i[j] - min) * color_coefficient);
      node.size = point_sizes[j];
      node.coordinates = coordinates + 2 * j;
      draw_node(canvas, status, &node);
      if (*status)
      {
        color_error_position(__FILE__, __LINE__);
        fputs("cannot draw node\n", stderr);
        return;
      }
    }
  }
}
