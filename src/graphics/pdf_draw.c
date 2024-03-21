#include "pdf_draw.h"
void pdf_draw(cairo_t * cr, double width, double height, void * a, drawer draw)
{
  cairo_save(cr);
  cairo_set_source_rgb(cr, 1, 1, 1);
  cairo_paint(cr);
  cairo_restore(cr);
  draw(cr, width, height, a);
  cairo_show_page(cr);
}
