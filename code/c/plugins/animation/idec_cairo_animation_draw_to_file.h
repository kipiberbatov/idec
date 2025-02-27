#include <cairo.h>

struct idec_animation;

void idec_cairo_animation_draw_to_file(
  struct idec_animation * animation,
  int * status,
  const char * filename,
  cairo_surface_t * (*_surface_create)(const char *, double, double),
  void (*_set_version)(cairo_surface_t * surface));
