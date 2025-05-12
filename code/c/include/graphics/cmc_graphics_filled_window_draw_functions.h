#ifndef _cmc_graphics_filled_window_draw_functions_h
#define _cmc_graphics_filled_window_draw_functions_h

struct cmc_graphics_filled_window_draw_functions
{
  void (*allocate_color)(void **, int *);
  void (*deallocate_color)(void *);
  void (*set_color)(void *, int *, int, int);
  void (*paint)(void *, int *, const void *);
};

#endif /* _cmc_graphics_filled_window_draw_functions_h */
