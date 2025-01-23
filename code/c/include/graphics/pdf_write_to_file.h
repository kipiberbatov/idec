#include <cairo.h>

void pdf_write_to_file(
  const char * filename,
  int * status,
  double width,
  double height,
  void * a,
  void (*draw)(cairo_t *, int *, double, double, const void *),
  int (*get_index)(const void *),
  int (*get_total_steps)(const void *),
  void (*increment_index)(void *));
