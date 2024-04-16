#include "pdf_draw.h"
#include "pdf_surface_draw.h"

void pdf_surface_draw(
  cairo_surface_t * surface,
  double width,
  double height,
  void * a,
  void (*draw)(cairo_t *, double, double, void *),
  int (*get_index)(const void *),
  int (*get_total_steps)(const void *),
  void (*increment_index)(void *))
{
  cairo_t * cr;
  int i, n;
  
  i = get_index(a);
  n = get_total_steps(a);
  while (i < n)
  {
    cr = cairo_create(surface);
    pdf_draw(cr, width, height, a, draw);
    increment_index(a);
    i = get_index(a);
    cairo_destroy(cr);
  }
}
