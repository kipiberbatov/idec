#include <cairo.h>

// #include "drawer.h"
// #include "get_index_t.h"
// #include "get_total_steps_t.h"

void pdf_surface_draw(
  cairo_surface_t * surface,
  double width,
  double height,
  void * a,
  void (*draw)(cairo_t *, double, double, void *),
  int (*get_index)(const void *),
  int (*get_total_steps)(const void *),
  void (*increment_index)(void *));
