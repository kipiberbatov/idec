#ifndef _idec_graphics_mesh_2d_1_cochain_sequence_draw_functions_h
#define _idec_graphics_mesh_2d_1_cochain_sequence_draw_functions_h

struct idec_graphics_mesh_2d_1_cochain_sequence;
struct idec_graphics_mesh_2d_edge;
struct idec_graphics_mesh_2d_skeleton;

struct idec_graphics_mesh_2d_1_cochain_sequence_draw_functions
{
  void (*set_background_color)(void *, int *);
  void (*draw_values)(
    void *,
    int *,
    const struct idec_graphics_mesh_2d_1_cochain_sequence *,
    int,
    int,
    void (*)(void *, int *, int, int),
    void (**)(void *, int *, const void *),
    void (*)(void *, int *, const struct idec_graphics_mesh_2d_edge *));
  void (*set_color)(void *, int *, int, int);
  void (*draw_oriented_edge)(
    void *, int *, const struct idec_graphics_mesh_2d_edge *);
  void (*draw_skeleton)(
    void *,
    int *,
    const struct idec_graphics_mesh_2d_skeleton *,
    void (**)(void *, int *, const void *),
    void (*)(void *, int *, const struct idec_graphics_mesh_2d_edge *));
  void (**draw_curves)(void *, int *, const void *);
  void (*draw_black_edge)(
    void *, int *, const struct idec_graphics_mesh_2d_edge *);
};

#endif /* _idec_graphics_mesh_2d_1_cochain_sequence_draw_functions_h */
