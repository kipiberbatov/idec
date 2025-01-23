#ifndef _idec_animation_h
#define _idec_animation_h

struct idec_animation_intrinsic_functions
{
  double (*get_width)(const void *);
  double (*get_height)(const void *);
  int (*get_total_steps)(const void *);
  int * (*get_old_index_address)(const void *);
  int * (*get_new_index_address)(const void *);
  void (*update_new_index)(void *);
};

struct idec_animation_canvas_functions
{
  void (*set_background_color)(void * canvas);

  void (*color_scheme)(
    void * canvas, int * status, int color_index, int total_colors);

  void (*draw)(
    void * canvas, int * status, const void * data, int total_colors,
    void (*)(void *, int *, int, int));
};

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

typedef void idec_animation_backend_t(
  struct idec_animation * animation,
  int * status,
  int argc,
  char ** argv,
  const char * output);

#endif /* _idec_animation_h */
