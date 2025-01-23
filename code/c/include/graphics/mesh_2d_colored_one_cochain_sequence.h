#ifndef _mesh_2d_colored_one_cochain_sequence_h
#define _mesh_2d_colored_one_cochain_sequence_h

#include "mesh.h"
#include "mesh_2d_colored_one_cochain.h"

typedef struct mesh_2d_colored_one_cochain_sequence
{
  int is_mesh_edge_skeleton;
  int index;
  int total_steps;
  mesh * m;
  double * bd_1;
  double * values;

  int total_colors;
  double * new_coordinates;
  double point_size;
  double line_width;
  double min_value;
  double max_value;
  void (*set_color)(cairo_t *, int *, int, int);
  void (*draw_skeleton)(
    cairo_t *, int *, const struct mesh_2d_colored_one_cochain *);
  void (*draw_values)(
    cairo_t *, int *, const struct mesh_2d_colored_one_cochain *);
} mesh_2d_colored_one_cochain_sequence;

int mesh_2d_colored_one_cochain_sequence_get_index_void(const void * a);
int mesh_2d_colored_one_cochain_sequence_get_total_steps_void(const void * a);
void mesh_2d_colored_one_cochain_sequence_increment_index_void(void * a);

void mesh_2d_colored_one_cochain_sequence_snapshot_cairo_draw(
  cairo_t * cr,
  int * status,
  double width,
  double height,
  const mesh_2d_colored_one_cochain_sequence * a);

void mesh_2d_colored_one_cochain_sequence_snapshot_cairo_draw_void(
  cairo_t * cr,
  int * status,
  double width,
  double height,
  const void * a);

#endif /* _mesh_2d_colored_one_cochain_sequence_h */
