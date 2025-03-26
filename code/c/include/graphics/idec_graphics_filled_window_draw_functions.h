#ifndef _idec_graphics_filled_window_draw_functions_h
#define _idec_graphics_filled_window_draw_functions_h

struct idec_graphics_filled_window_draw_functions
{
  void (*allocate_color)(void **, int *);
  void (*deallocate_color)(void *);
  void (*set_color)(void *, int *, int, int);
  void (*paint)(void *, int *, const void *);
};

#endif /* _idec_graphics_filled_window_draw_functions_h */
