#ifndef _idec_graphics_filled_window_draw_functions_h
#define _idec_graphics_filled_window_draw_functions_h

struct idec_graphics_filled_window_draw_functions
{
  void (*set_color)(void *, int *, int, int);
  void (*paint)(void *, int *, int, int, void (*)(void *, int *, int, int));
};

#endif /* _idec_graphics_filled_window_draw_functions_h */
