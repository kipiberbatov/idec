#include <cairo.h>
#include <gtk/gtk.h>

void gtk_draw(
  GtkWidget * widget,
  cairo_t * cr,
  void * a,
  void (*draw)(cairo_t *, double, double, const void *),
  int (*get_index)(const void *),
  int (*get_total_steps)(const void *),
  void (*increment_index)(void *));
