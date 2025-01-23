#include <cairo.h>
#include <gtk/gtk.h>

void gtk_run(
  int (*draw_event)(GtkWidget *, cairo_t * cr, void *),
  void * a,
  double width,
  double height,
  int timelapse,
  const char * title);
