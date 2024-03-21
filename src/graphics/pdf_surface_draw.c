#include "pdf_draw.h"
#include "pdf_surface_draw.h"

void pdf_surface_draw(
  cairo_surface_t * surface,
  double width,
  double height,
  void * a,
  drawer draw,
  get_index_t get_index,
  get_total_steps_t get_total_steps)
{
  cairo_t * cr;
  int n;
  int * i;
  
  i = get_index(a);
  n = get_total_steps(a);
  while (*i < n - 1)
  {
    cr = cairo_create(surface);
    pdf_draw(cr, width, height, a, draw);
    *i += 1;
    cairo_destroy(cr);
  }
}
