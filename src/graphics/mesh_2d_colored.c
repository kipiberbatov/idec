#include <math.h>

#include "double.h"
#include "mesh_2d_colored.h"

/********************************** 0-cells ***********************************/

struct mesh_2d_colored_node
{
  int total_colors;
  double * coordinates;
  double size;
  double relative_value;
  painter paint;
};

void mesh_2d_colored_node_cairo_draw(
  cairo_t * cr,
  mesh_2d_colored_node * node)
{
  int ind;
  
  ind = (int) (node->relative_value * ((double) (node->total_colors - 1)));
  node->paint(cr, ind, node->total_colors);
  /* cairo_set_line_width(cr, 1);  */
  cairo_arc(cr, node->coordinates[0], node->coordinates[1],
    node->size, 0, 2 * M_PI);
  
  cairo_fill(cr);
  cairo_stroke(cr);
}

struct mesh_2d_colored_zero_cochain
{
  int number_of_nodes;
  int total_colors;
  double * coordinates;
  double * values;
  double point_size;
  double min_value;
  double max_value;
  painter paint;
};

void mesh_2d_colored_zero_cochain_cairo_draw(
  cairo_t * cr,
  const mesh_2d_colored_zero_cochain * c)
{
  int c_number_of_nodes, j;
  double c_max, c_min, denominator;
  double * c_coordinates, * c_values;
  mesh_2d_colored_node node;
  
  c_min = c->min_value;
  c_max = c->max_value;
  c_number_of_nodes = c->number_of_nodes;
  c_coordinates = c->coordinates;
  c_values = c->values;
  node.size = c->point_size;
  node.total_colors = c->total_colors;
  node.paint = c->paint;
  denominator = c_max - c_min;
  for (j = 0; j < c_number_of_nodes; ++j)
  {
    node.coordinates = c_coordinates + 2 * j;
    node.relative_value = (c_values[j] - c_min) / denominator;
    mesh_2d_colored_node_cairo_draw(cr, &node);
  }
}

int mesh_2d_colored_zero_cochain_sequence_get_index_void(const void * a)
{
  return ((const mesh_2d_colored_zero_cochain_sequence *) a)->index;
}

int mesh_2d_colored_zero_cochain_sequence_get_total_steps_void(const void * a)
{
  return ((const mesh_2d_colored_zero_cochain_sequence *) a)->total_steps;
}

void mesh_2d_colored_zero_cochain_sequence_increment_index_void(void * a)
{
  ++((mesh_2d_colored_zero_cochain_sequence *) a)->index;
}

void mesh_2d_colored_zero_cochain_sequence_snapshot_cairo_draw(
  cairo_t * cr,
  double width,
  double height,
  mesh_2d_colored_zero_cochain_sequence * a)
{
  int i;
  mesh_2d_colored_zero_cochain c;
  
  i = a->index;
  c.number_of_nodes = a->m->cn[0];
  c.total_colors = a->total_colors;
  c.coordinates = a->new_coordinates;
  c.values = a->values + c.number_of_nodes * i;
  c.point_size = a->point_size;
  c.min_value = a->min_value;
  c.max_value = a->max_value;
  c.paint = a->paint;
  mesh_2d_colored_zero_cochain_cairo_draw(cr, &c);
}

void mesh_2d_colored_zero_cochain_sequence_snapshot_cairo_draw_void(
  cairo_t * cr,
  double width,
  double height,
  void * a)
{
  mesh_2d_colored_zero_cochain_sequence_snapshot_cairo_draw(
    cr,
    width,
    height,
    (mesh_2d_colored_zero_cochain_sequence *) a);
}

/********************************** 1-cells ***********************************/ 

struct mesh_2d_colored_edge
{
  int total_colors;
  double * coordinates_0;
  double * coordinates_1;
  double width;
  double relative_value;
  painter paint;
};

void mesh_2d_colored_edge_cairo_draw(
  cairo_t * cr,
  mesh_2d_colored_edge * edge)
{
  int ind;
  
  ind = (int) (edge->relative_value * ((double) (edge->total_colors - 1)));
  edge->paint(cr, ind, edge->total_colors);
  cairo_set_line_width(cr, edge->width);
  cairo_move_to(cr, edge->coordinates_0[0], edge->coordinates_0[1]);
  cairo_line_to(cr, edge->coordinates_1[0], edge->coordinates_1[1]);
  cairo_stroke(cr);
}

struct mesh_2d_colored_one_cochain
{
  int total_colors;
  jagged2 * cf_1_0;
  double * coordinates;
  double * values;
  double line_width;
  double min_value;
  double max_value;
  painter paint;
};

void mesh_2d_colored_one_cochain_cairo_draw(
  cairo_t * cr,
  const mesh_2d_colored_one_cochain * c)
{
  int c_number_of_edges, i;
  double c_max, c_min, denominator;
  double * c_coordinates, * c_values;
  mesh_2d_colored_edge edge;
  jagged1 cf_1_0_i;
  jagged2 * cf_1_0;
  
  c_min = c->min_value;
  c_max = c->max_value;
  c_coordinates = c->coordinates;
  c_values = c->values;
  edge.width = c->line_width;
  edge.total_colors = c->total_colors;
  edge.paint = c->paint;
  denominator = c_max - c_min;
  cf_1_0 = c->cf_1_0;
  c_number_of_edges = cf_1_0->a0;
  for (i = 0; i < c_number_of_edges; ++i)
  {
    jagged2_part1(&cf_1_0_i, cf_1_0, i);
    edge.coordinates_0 = c_coordinates + 2 * cf_1_0_i.a1[0];
    edge.coordinates_1 = c_coordinates + 2 * cf_1_0_i.a1[1];
    edge.relative_value = (c_values[i] - c_min) / denominator;
    mesh_2d_colored_edge_cairo_draw(cr, &edge);
  }
}

int mesh_2d_colored_one_cochain_sequence_get_index_void(const void * a)
{
  return ((const mesh_2d_colored_one_cochain_sequence *) a)->index;
}

int mesh_2d_colored_one_cochain_sequence_get_total_steps_void(const void * a)
{
  return ((const mesh_2d_colored_one_cochain_sequence *) a)->total_steps;
}

void mesh_2d_colored_one_cochain_sequence_increment_index_void(void * a)
{
  ++((mesh_2d_colored_one_cochain_sequence *) a)->index;
}

void mesh_2d_colored_one_cochain_sequence_snapshot_cairo_draw(
  cairo_t * cr,
  double width,
  double height,
  mesh_2d_colored_one_cochain_sequence * a)
{
  int i;
  mesh * m;
  mesh_2d_colored_one_cochain c;
  jagged2 c_cf_1_0;
  
  m = a->m;
  i = a->index;
  
  mesh_cf_part2(&c_cf_1_0, m, 1, 0);
  c.cf_1_0 = &c_cf_1_0;
  c.total_colors = a->total_colors;
  c.coordinates = a->new_coordinates;
  c.values = a->values + m->cn[1] * i;
  c.line_width = a->line_width;
  c.min_value = a->min_value;
  c.max_value = a->max_value;
  c.paint = a->paint;
  mesh_2d_colored_one_cochain_cairo_draw(cr, &c);
}

void mesh_2d_colored_one_cochain_sequence_snapshot_cairo_draw_void(
  cairo_t * cr,
  double width,
  double height,
  void * a)
{
  mesh_2d_colored_one_cochain_sequence_snapshot_cairo_draw(
    cr,
    width,
    height,
    (mesh_2d_colored_one_cochain_sequence *) a);
}
