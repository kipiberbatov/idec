#ifndef _cmc_graphics_mesh_2d_0_cochain_sequence_draw_functions_h
#define _cmc_graphics_mesh_2d_0_cochain_sequence_draw_functions_h

struct cmc_graphics_mesh_2d_0_cochain_sequence;
struct cmc_graphics_mesh_2d_edge;
struct cmc_graphics_mesh_2d_node;
struct cmc_graphics_mesh_2d_skeleton;

struct cmc_graphics_mesh_2d_0_cochain_sequence_draw_functions
{
  void (*allocate_color)(void **, int *);
  void (*deallocate_color)(void *);
  void (*set_background_color)(void *, int *);
  void (*draw_values)(
    void *,
    int *,
    const struct cmc_graphics_mesh_2d_0_cochain_sequence *,
    int,
    int,
    const struct cmc_graphics_mesh_2d_0_cochain_sequence_draw_functions *
      functions);
  void (*check_color_scheme)(int *, int);
  void (*set_color)(void *, int, int);
  void (*draw_node)(void *, int *, const struct cmc_graphics_mesh_2d_node *,
                    void (*)(void *, const void *));
  void (*get_color)(void *, const void *);
  void (*draw_skeleton)(
    void *,
    int *,
    const struct cmc_graphics_mesh_2d_skeleton *,
    void (**)(void *, int *, const void *),
    void (*)(void *, int *, const struct cmc_graphics_mesh_2d_edge *,
    void (*)(void *, int *, const void *)));
  void (**draw_curves)(void *, int *, const void *);
  void (*draw_black_edge)(
    void *, int *, const struct cmc_graphics_mesh_2d_edge *,
    void (*)(void *, int *, const void *));
};

#endif /* _cmc_graphics_mesh_2d_0_cochain_sequence_draw_functions_h */
