#ifndef _cmc_graphics_filled_window_h
#define _cmc_graphics_filled_window_h

struct cmc_animation;

struct cmc_graphics_filled_window
{
  void * color;
};

void cmc_graphics_filled_window_draw_snapshot(
  void * canvas,
  int * status,
  const struct cmc_animation * animation);

#endif /* _cmc_graphics_filled_window_h */
