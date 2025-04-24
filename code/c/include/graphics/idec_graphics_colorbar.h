#ifndef _idec_graphics_colorbar_h
#define _idec_graphics_colorbar_h

enum idec_graphics_colorbar_direction;
struct idec_graphics_colorbar_draw_functions;

void idec_graphics_colorbar_draw_values(
  void * canvas,
  int * status,
  double width,
  double height,
  enum idec_graphics_colorbar_direction direction,
  int total_colors,
  const struct idec_graphics_colorbar_draw_functions * functions);

struct idec_animation;

void idec_graphics_colorbar_draw_snapshot(
  void * canvas,
  int * status,
  const struct idec_animation * animation);

#endif /* _idec_graphics_colorbar_h */
