#ifndef _idec_graphics_mesh_2d_skeleton_draw_functions_h
#define _idec_graphics_mesh_2d_skeleton_draw_functions_h

struct idec_graphics_mesh_2d_edge;
struct idec_graphics_mesh_2d_skeleton;

struct idec_graphics_mesh_2d_skeleton_draw_functions
{
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

#endif /* _idec_graphics_mesh_2d_skeleton_draw_functions_h */
