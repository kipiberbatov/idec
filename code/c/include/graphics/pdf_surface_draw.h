#include <cairo.h>

void pdf_surface_draw(
  cairo_surface_t * surface,
  int * status,
  double width,
  double height,
  void * a,
  void (*draw)(cairo_t *, int *, double, double, const void *),
  int (*get_index)(const void *),
  int (*get_total_steps)(const void *),
  void (*increment_index)(void *));
