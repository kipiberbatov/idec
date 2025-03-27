#ifndef _idec_graphics_mesh_2d_0_cochain_sequence_draw_functions_h
#define _idec_graphics_mesh_2d_0_cochain_sequence_draw_functions_h

struct idec_graphics_mesh_2d_0_cochain_sequence;
struct idec_graphics_mesh_2d_edge;
struct idec_graphics_mesh_2d_node;
struct idec_graphics_mesh_2d_skeleton;

struct idec_graphics_mesh_2d_0_cochain_sequence_draw_functions
{
  void (*allocate_color)(void **, int *);
  void (*deallocate_color)(void *);
  void (*set_background_color)(void *, int *);
  void (*draw_values)(
    void *,
    int *,
    const struct idec_graphics_mesh_2d_0_cochain_sequence *,
    int,
    int,
    const struct idec_graphics_mesh_2d_0_cochain_sequence_draw_functions *
      functions);
  void (*check_color_scheme)(int *, int);
  void (*set_color)(void *, int, int);
  void (*draw_node)(void *, int *, const struct idec_graphics_mesh_2d_node *,
                    void (*)(void *, int *, const void *));
  void (*set_source)(void *, int *, const void *);
  void (*draw_skeleton)(
    void *,
    int *,
    const struct idec_graphics_mesh_2d_skeleton *,
    void (**)(void *, int *, const void *),
    void (*)(void *, int *, const struct idec_graphics_mesh_2d_edge *,
    void (*)(void *, int *, const void *)));
  void (**draw_curves)(void *, int *, const void *);
  void (*draw_black_edge)(
    void *, int *, const struct idec_graphics_mesh_2d_edge *,
    void (*)(void *, int *, const void *));
};

#endif /* _idec_graphics_mesh_2d_0_cochain_sequence_draw_functions_h */
