#ifndef _idec_graphics_mesh_2d_0_cochain_sequence_h
#define _idec_graphics_mesh_2d_0_cochain_sequence_h

#include "mesh.h"

/* used in conjunction with idec_animation_generic_data */
struct idec_graphics_mesh_2d_0_cochain_sequence
{
  mesh * m;
  double * values;
  double * coordinates;
  double * point_sizes;
  double line_width;
  double min_value;
  double max_value;
};

struct idec_graphics_mesh_2d_0_cochain_sequence_draw_functions;
struct idec_graphics_mesh_2d_node;

void idec_graphics_mesh_2d_0_cochain_sequence_draw_values(
  void * canvas,
  int * status,
  const struct idec_graphics_mesh_2d_0_cochain_sequence * cochain_sequence,
  int i,
  int total_colors,
  const struct idec_graphics_mesh_2d_0_cochain_sequence_draw_functions *
    functions);

struct idec_animation;

void idec_graphics_mesh_2d_0_cochain_sequence_draw_snapshot(
  void * canvas,
  int * status,
  const struct idec_animation * animation);

#endif /* _idec_graphics_mesh_2d_0_cochain_sequence_h */
