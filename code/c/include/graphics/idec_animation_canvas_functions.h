#ifndef _idec_animation_canvas_functions_h
#define _idec_animation_canvas_functions_h

struct idec_animation_canvas_functions
{
  void (*set_background_color)(void * canvas);

  void (*set_color)(
    void * canvas, int * status, int color_index, int total_colors);

  void (*draw_snapshot)(
    void * canvas, int * status, const void * data, int total_colors,
    void (*)(void *, int *, int, int));
};

#endif /* _idec_animation_canvas_functions_h */
