#ifndef _idec_filled_window_h
#define _idec_filled_window_h

struct idec_filled_window
{
  int width;
  int height;
  int old_index;
  int new_index;
  int total_colors;
};

extern const struct idec_animation_intrinsic_functions *
idec_filled_window_intrinsic_functions;

extern const struct idec_animation_canvas_functions *
idec_filled_window_canvas_functions;

#endif /* _idec_filled_window_h */
