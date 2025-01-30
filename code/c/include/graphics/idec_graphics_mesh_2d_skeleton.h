#ifndef _idec_graphics_mesh_2d_skeleton_h
#define _idec_graphics_mesh_2d_skeleton_h

struct idec_animation;
struct idec_graphics_mesh_2d_edge;
struct mesh;

struct idec_graphics_mesh_2d_skeleton
{
  struct mesh * m;
  double * coordinates;
  double line_width;
};

void idec_graphics_mesh_2d_skeleton_draw(
  void * canvas,
  int * status,
  const struct idec_graphics_mesh_2d_skeleton * skeleton,
  void (*draw_edge)(void *, int *, const struct idec_graphics_mesh_2d_edge *));

void idec_graphics_mesh_2d_skeleton_draw_snapshot(
  void * canvas,
  int * status,
  const struct idec_animation * animation);

#endif /* _idec_graphics_mesh_2d_skeleton_h */
