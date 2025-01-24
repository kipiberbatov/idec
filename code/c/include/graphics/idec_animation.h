#ifndef _idec_animation_h
#define _idec_animation_h

struct idec_animation
{
  void * data;
  const struct idec_animation_intrinsic_functions * intrinsic_functions;
  const struct idec_animation_canvas_functions * canvas_functions;
  int total_colors;
  int timelapse;
  int close_automatically;
  char * title;
};

#endif /* _idec_animation_h */
