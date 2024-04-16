#include <cairo.h>

void pdf_write_to_file(
  const char * filename,
  double width,
  double height,
  void * a,
  void (*draw)(cairo_t *, double, double, void *),
  int (*get_index)(const void *),
  int (*get_total_steps)(const void *),
  void (*increment_index)(void *));
