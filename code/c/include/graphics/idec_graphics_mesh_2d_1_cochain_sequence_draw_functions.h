#ifndef _idec_graphics_mesh_2d_1_cochain_sequence_draw_functions_h
#define _idec_graphics_mesh_2d_1_cochain_sequence_draw_functions_h

struct idec_graphics_mesh_2d_edge;

struct idec_graphics_mesh_2d_1_cochain_sequence_draw_functions
{
  void (*set_background_color)(void *, int *);
  void (*draw_black_edge)(
    void *, int *, const struct idec_graphics_mesh_2d_edge *);
  void (*set_color)(void *, int *, int, int);
  void (*draw_oriented_edge)(
    void *, int *, const struct idec_graphics_mesh_2d_edge *);
};

#endif /* _idec_graphics_mesh_2d_1_cochain_sequence_draw_functions_h */
