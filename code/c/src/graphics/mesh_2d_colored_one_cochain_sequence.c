#include "mesh_2d_colored_edge.h"
#include "mesh_2d_colored_one_cochain.h"
#include "mesh_2d_colored_one_cochain_sequence.h"

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
  const mesh_2d_colored_one_cochain_sequence * a)
{
  int i;
  mesh * m;
  mesh_2d_colored_one_cochain c;
  jagged2 c_cf_1_0;

  m = a->m;
  i = a->index;

  c.is_mesh_edge_skeleton = a->is_mesh_edge_skeleton;
  c.total_colors = a->total_colors;
  mesh_cf_part2(&c_cf_1_0, m, 1, 0);
  c.cf_1_0 = &c_cf_1_0;
  c.bd_1 = a->bd_1;
  c.coordinates = a->new_coordinates;
  c.values = a->values + m->cn[1] * i;
  c.point_size = a->point_size;
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
  const void * a)
{
  mesh_2d_colored_one_cochain_sequence_snapshot_cairo_draw(
    cr,
    width,
    height,
    (const mesh_2d_colored_one_cochain_sequence *) a);
}
