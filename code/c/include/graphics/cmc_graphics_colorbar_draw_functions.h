#ifndef _cmc_graphics_colorbar_draw_functions_h
#define _cmc_graphics_colorbar_draw_functions_h

struct cmc_graphics_rectangle;
enum cmc_graphics_colorbar_direction;

struct cmc_graphics_colorbar_draw_functions
{
  void (*allocate_color)(void **, int *);
  void (*deallocate_color)(void *);
  void (*draw_rectangles)(
    struct cmc_graphics_rectangle *,
    void *,
    int *,
    double,
    double,
    enum cmc_graphics_colorbar_direction,
    int,
    const struct cmc_graphics_colorbar_draw_functions * functions);
  void (*check_color_scheme)(int *, int);
  void (*set_color)(void *, int, int);
  void (*draw_rectangle)(void *, int *, const struct cmc_graphics_rectangle *,
                         void (*)(void *, const void *));
  void (*get_color)(void *, const void *);
};

#endif /* _cmc_graphics_colorbar_draw_functions_h */
