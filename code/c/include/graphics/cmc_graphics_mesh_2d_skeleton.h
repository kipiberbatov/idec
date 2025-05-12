#ifndef _cmc_graphics_mesh_2d_skeleton_h
#define _cmc_graphics_mesh_2d_skeleton_h

struct cmc_animation;
struct cmc_graphics_mesh_2d_edge;
struct mesh;

struct cmc_graphics_mesh_2d_skeleton
{
  struct mesh * m;
  double * coordinates;
  double line_width;
};

void cmc_graphics_mesh_2d_skeleton_draw(
  void * canvas,
  int * status,
  const struct cmc_graphics_mesh_2d_skeleton * skeleton,
  void (**draw_curves)(void *, int *, const void *),
  void (*draw_black_edge)(
    void *, int *, const struct cmc_graphics_mesh_2d_edge *,
    void (*)(void *, int *, const void *)));

void cmc_graphics_mesh_2d_skeleton_draw_polar(
  void * canvas,
  int * status,
  const struct cmc_graphics_mesh_2d_skeleton * skeleton,
  void (**draw_curves)(void *, int *, const void *),
  void (*draw_black_edge)(
    void *, int *, const struct cmc_graphics_mesh_2d_edge *,
    void (*)(void *, int *, const void *)));

void cmc_graphics_mesh_2d_skeleton_draw_polar_forman(
  void * canvas,
  int * status,
  const struct cmc_graphics_mesh_2d_skeleton * skeleton,
  void (**draw_curves)(void *, int *, const void *),
  void (*draw_black_edge)(
    void *, int *, const struct cmc_graphics_mesh_2d_edge *,
    void (*)(void *, int *, const void *)));

void cmc_graphics_mesh_2d_skeleton_draw_snapshot(
  void * canvas,
  int * status,
  const struct cmc_animation * animation);

#endif /* _cmc_graphics_mesh_2d_skeleton_h */
