#ifndef _cmc_graphics_mesh_2d_skeleton_draw_functions_h
#define _cmc_graphics_mesh_2d_skeleton_draw_functions_h

struct cmc_graphics_mesh_2d_edge;
struct cmc_graphics_mesh_2d_skeleton;

struct cmc_graphics_mesh_2d_skeleton_draw_functions
{
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

#endif /* _cmc_graphics_mesh_2d_skeleton_draw_functions_h */
