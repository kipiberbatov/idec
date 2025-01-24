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

void idec_animation_read_and_apply_backends(
  struct idec_animation * animation,
  int * status,
  int argc,
  char ** argv,
  const char * output_name,
  const char * canvas_library,
  const char * canvas_backend,
  const char * animation_library,
  const char * animation_backend);

void idec_animation_check_input(
  int * status, const struct idec_animation * animation);

#endif /* _idec_animation_h */
