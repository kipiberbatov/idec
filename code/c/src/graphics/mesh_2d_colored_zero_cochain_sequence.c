#include "mesh_2d_colored_zero_cochain.h"
#include "mesh_2d_colored_zero_cochain_sequence.h"

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
  int * status,
  double width,
  double height,
  const mesh_2d_colored_zero_cochain_sequence * a)
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
  c.set_color = a->set_color;
  mesh_2d_colored_zero_cochain_cairo_draw(cr, status, &c);
}

void mesh_2d_colored_zero_cochain_sequence_snapshot_cairo_draw_void(
  cairo_t * cr,
  int * status,
  double width,
  double height,
  const void * a)
{
  mesh_2d_colored_zero_cochain_sequence_snapshot_cairo_draw(
    cr,
    status,
    width,
    height,
    (const mesh_2d_colored_zero_cochain_sequence *) a);
}
