#include <cairo.h>

#include "drawer.h"
#include "get_index_t.h"
#include "get_total_steps_t.h"

void pdf_surface_draw(
  cairo_surface_t * surface,
  double width,
  double height,
  void * a,
  drawer draw,
  get_index_t get_index,
  get_total_steps_t get_total_steps);
