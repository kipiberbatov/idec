#include <cairo.h>
#include <gtk/gtk.h>

#include "drawer.h"
#include "get_index_t.h"
#include "get_total_steps_t.h"

void gtk_draw(
  GtkWidget * widget,
  cairo_t * cr,
  void * a,
  drawer draw,
  get_index_t get_index,
  get_total_steps_t get_total_steps);
