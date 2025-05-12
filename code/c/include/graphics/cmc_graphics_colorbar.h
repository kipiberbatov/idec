#ifndef _cmc_graphics_colorbar_h
#define _cmc_graphics_colorbar_h

enum cmc_graphics_colorbar_direction;
struct cmc_graphics_colorbar_draw_functions;
struct cmc_graphics_rectangle;

void cmc_graphics_colorbar_draw_rectangles(
  struct cmc_graphics_rectangle * rectangle,
  void * canvas,
  int * status,
  double width,
  double height,
  enum cmc_graphics_colorbar_direction direction,
  int total_colors,
  const struct cmc_graphics_colorbar_draw_functions * functions);

struct cmc_animation;

void cmc_graphics_colorbar_draw_snapshot(
  void * canvas,
  int * status,
  const struct cmc_animation * animation);

#endif /* _cmc_graphics_colorbar_h */
