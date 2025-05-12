#ifndef _cmc_animation_h
#define _cmc_animation_h

struct cmc_animation
{
  void * data;
  struct cmc_animation_generic_data * generic_data;
  void (*update_new_index)(int *);
  const void * draw_functions;
  void (*draw_snapshot)(void *, int *, const struct cmc_animation *);
  int total_colors;
  int timelapse;
  int close_automatically;
  char * title;
};

void cmc_animation_read_and_apply_backends(
  struct cmc_animation * animation,
  int * status,
  int argc,
  char ** argv,
  const char * output_name,
  const char * canvas_library,
  const char * canvas_backend,
  const char * animation_library,
  const char * animation_backend);

void cmc_animation_check_input(
  int * status, const struct cmc_animation * animation);

#endif /* _cmc_animation_h */
