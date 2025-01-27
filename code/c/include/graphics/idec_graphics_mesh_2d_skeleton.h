#ifndef _idec_graphics_mesh_2d_skeleton_h
#define _idec_graphics_mesh_2d_skeleton_h

struct mesh;

struct idec_graphics_mesh_2d_skeleton
{
  struct mesh * m;
  double * coordinates;
  double line_width;
};

struct idec_graphics_mesh_2d_edge;

void idec_graphics_mesh_2d_skeleton_draw(
  void * canvas,
  int * status,
  const struct idec_graphics_mesh_2d_skeleton * skeleton,
  void (*draw_edge)(void *, int *, const struct idec_graphics_mesh_2d_edge *));

#endif /* _idec_graphics_mesh_2d_skeleton_h */
