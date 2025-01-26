#ifndef _idec_graphics_mesh_2d_0_cochain_sequence_h
#define _idec_graphics_mesh_2d_0_cochain_sequence_h

/* used in conjunction with idec_animation_generic_data */
struct idec_graphics_mesh_2d_0_cochain_sequence
{
  int number_of_nodes;
  double * values;
  double * coordinates;
  double * point_sizes;
  double min_value;
  double max_value;
};

struct idec_graphics_mesh_2d_node;

void idec_graphics_mesh_2d_0_cochain_sequence_draw_snapshot(
  void * canvas,
  int * status,
  const struct idec_graphics_mesh_2d_0_cochain_sequence * cochain_sequence,
  const struct idec_animation_generic_data * generic_data,
  int total_colors,
  void (*set_color)(void *, int *, int, int),
  void (*node_draw)(void *, int *, const struct idec_graphics_mesh_2d_node *));

#endif /* _idec_graphics_mesh_2d_0_cochain_sequence_h */
