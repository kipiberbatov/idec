#ifndef _idec_graphics_filled_window_h
#define _idec_graphics_filled_window_h

struct idec_animation;

struct idec_graphics_filled_window
{
  void * color;
};

void idec_graphics_filled_window_draw_snapshot(
  void * canvas,
  int * status,
  const struct idec_animation * animation);

#endif /* _idec_graphics_filled_window_h */
