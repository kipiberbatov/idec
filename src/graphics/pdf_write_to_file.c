#include <cairo.h>
#include <cairo-pdf.h>

#include "pdf_surface_draw.h"
#include "pdf_write_to_file.h"

void pdf_write_to_file(
  const char * filename,
  double width,
  double height,
  void * a,
  drawer draw,
  get_index_t get_index,
  get_total_steps_t get_total_steps)
{
  cairo_surface_t * surface;

  surface = cairo_pdf_surface_create(filename, width, height);
  pdf_surface_draw(
    surface, width, height, a, draw, get_index, get_total_steps);
  cairo_surface_destroy(surface);
}
