#ifndef _idec_graphics_mesh_2d_skeleton_draw_functions_h
#define _idec_graphics_mesh_2d_skeleton_draw_functions_h

struct idec_graphics_mesh_2d_edge;

struct idec_graphics_mesh_2d_skeleton_draw_functions
{
  void (*draw_edge)(void *, int *, const struct idec_graphics_mesh_2d_edge *);
};

#endif /* _idec_graphics_mesh_2d_skeleton_draw_functions_h */
