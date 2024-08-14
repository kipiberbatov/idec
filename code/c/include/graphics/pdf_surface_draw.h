#include <cairo.h>

void pdf_surface_draw(
  cairo_surface_t * surface,
  double width,
  double height,
  void * a,
  void (*draw)(cairo_t *, double, double, const void *),
  int (*get_index)(const void *),
  int (*get_total_steps)(const void *),
  void (*increment_index)(void *));
