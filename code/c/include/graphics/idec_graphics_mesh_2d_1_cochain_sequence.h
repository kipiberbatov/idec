#ifndef _idec_graphics_mesh_2d_1_cochain_sequence_h
#define _idec_graphics_mesh_2d_1_cochain_sequence_h

struct mesh;

/* used in conjunction with idec_animation_generic_data */
struct idec_graphics_mesh_2d_1_cochain_sequence
{
  struct mesh * m;
  double * values;
  double * coordinates;
  double * boundary_1;
  double line_width;
  double min_value;
  double max_value;
};

struct idec_graphics_mesh_2d_edge;
struct idec_animation;
struct idec_animation_generic_data;

void idec_graphics_mesh_2d_1_cochain_sequence_draw_values(
  void * canvas,
  int * status,
  const struct idec_graphics_mesh_2d_1_cochain_sequence * cochain_sequence,
  const struct idec_animation_generic_data * generic_data,
  int total_colors,
  void (*set_color)(void *, int *, int, int),
  void (**draw_curves)(void *, int *, const void *),
  void (*draw_edge)(void *, int *, const struct idec_graphics_mesh_2d_edge *));

void idec_graphics_mesh_2d_1_cochain_sequence_draw_snapshot(
  void * canvas,
  int * status,
  const struct idec_animation * animation);

#endif /* _idec_graphics_mesh_2d_1_cochain_sequence_h */
