#ifndef _idec_graphics_colorbar_draw_functions_h
#define _idec_graphics_colorbar_draw_functions_h

struct idec_graphics_rectangle;
enum idec_graphics_colorbar_direction;

struct idec_graphics_colorbar_draw_functions
{
  void (*allocate_color)(void **, int *);
  void (*deallocate_color)(void *);
  void (*draw_rectangles)(
    struct idec_graphics_rectangle *,
    void *,
    int *,
    double,
    double,
    enum idec_graphics_colorbar_direction,
    int,
    const struct idec_graphics_colorbar_draw_functions * functions);
  void (*check_color_scheme)(int *, int);
  void (*set_color)(void *, int, int);
  void (*draw_rectangle)(void *, int *, const struct idec_graphics_rectangle *,
                         void (*)(void *, const void *));
  void (*get_color)(void *, const void *);
};

#endif /* _idec_graphics_colorbar_draw_functions_h */
