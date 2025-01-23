#include <cairo.h>

void pdf_draw(
  cairo_t * cr,
  int * status,
  double width,
  double height,
  void * a,
  void (*draw)(cairo_t *, int *, double, double, const void *));
