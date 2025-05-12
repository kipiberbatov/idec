#ifndef _cmc_graphics_mesh_2d_0_cochain_sequence_h
#define _cmc_graphics_mesh_2d_0_cochain_sequence_h

#include "mesh.h"

/* used in conjunction with cmc_animation_generic_data */
struct cmc_graphics_mesh_2d_0_cochain_sequence
{
  mesh * m;
  double * values;
  double * coordinates;
  double * point_sizes;
  double line_width;
  double min_value;
  double max_value;
};

struct cmc_graphics_mesh_2d_0_cochain_sequence_draw_functions;
struct cmc_graphics_mesh_2d_node;

void cmc_graphics_mesh_2d_0_cochain_sequence_draw_values(
  void * canvas,
  int * status,
  const struct cmc_graphics_mesh_2d_0_cochain_sequence * cochain_sequence,
  int i,
  int total_colors,
  const struct cmc_graphics_mesh_2d_0_cochain_sequence_draw_functions *
    functions);

struct cmc_animation;

void cmc_graphics_mesh_2d_0_cochain_sequence_draw_snapshot(
  void * canvas,
  int * status,
  const struct cmc_animation * animation);

#endif /* _cmc_graphics_mesh_2d_0_cochain_sequence_h */
