#include <cairo.h>
#include <gtk/gtk.h>

void gtk_draw(
  GtkWidget * widget,
  cairo_t * cr,
  void * a,
  int * status,
  void (*draw)(cairo_t *, int *, double, double, const void *),
  int (*get_index)(const void *),
  int (*get_total_steps)(const void *),
  void (*increment_index)(void *));
