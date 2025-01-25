#include <math.h>
#include <stdio.h>

#include <cairo.h>

#include "color.h"
#include "idec_animation_canvas_functions.h"
#include "idec_animation_generic_data.h"
#include "idec_graphics_mesh_2d_0_cochain_sequence.h"
#include "idec_set_color_from_scheme_rainbow.h"

static void set_background_color_white(void * canvas)
{
  cairo_set_source_rgb((cairo_t *) canvas, 1, 1, 1);
}

struct idec_node
{
  int total_colors;
  double * coordinates;
  double size;
  double relative_value;
  void (*set_color)(void *, int *, int, int);
};

static void idec_node_cairo_draw(
  cairo_t * cr,
  int * status,
  const struct idec_node * node)
{
  int ind;
  double * coordinates = node->coordinates;

  ind = (int) (node->relative_value * ((double) (node->total_colors - 1)));
  node->set_color(cr, status, ind, node->total_colors);
  cairo_arc(cr, coordinates[0], coordinates[1], node->size, 0, 2 * M_PI);
  cairo_fill(cr);
  cairo_stroke(cr);
}

static void draw_snapshot(
  void * canvas,
  int * status,
  const void * data,
  const struct idec_animation_generic_data * generic_data,
  int total_colors,
  void (*set_color)(void *, int *, int, int))
{
  int i, j, number_of_nodes;
  double max, min, denominator;
  double * coordinates, * point_sizes, * values_i;
  struct idec_node node;
  cairo_t * cr;
  const struct idec_graphics_mesh_2d_0_cochain_sequence * object;

  cr = (cairo_t *) canvas;
  object = (const struct idec_graphics_mesh_2d_0_cochain_sequence *) data;

  min = object->min_value;
  max = object->max_value;
  number_of_nodes = object->number_of_nodes;
  node.total_colors = total_colors;
  node.set_color = set_color;
  denominator = max - min;
  point_sizes = object->point_sizes;
  coordinates = object->coordinates;

  i = generic_data->new_index;
  values_i = object->values + number_of_nodes * i;
  if (denominator == 0.)
  {
    node.relative_value = 0.;
    for (j = 0; j < number_of_nodes; ++j)
    {
      node.size = point_sizes[j];
      node.coordinates = coordinates + 2 * j;
      idec_node_cairo_draw(cr, status, &node);
    }
  }
  else
    for (j = 0; j < number_of_nodes; ++j)
    {
      node.size = point_sizes[j];
      node.coordinates = coordinates + 2 * j;
      node.relative_value = (values_i[j] - min) / denominator;
      idec_node_cairo_draw(cr, status, &node);
    }
}

/* This variable will be resolved at runtime by its address */
const struct idec_animation_canvas_functions
idec_graphics_mesh_2d_0_cochain_sequence_canvas_functions_cairo =
{
  set_background_color_white,
  (void (*)(void *, int *, int, int)) idec_set_color_from_scheme_rainbow,
  draw_snapshot
};
