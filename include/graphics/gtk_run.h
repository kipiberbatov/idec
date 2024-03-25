#ifndef _gtk_run_h
#define _gtk_run_h

#include <cairo.h>
#include <gtk/gtk.h>

typedef int (*gtk_draw_event_function)(
  GtkWidget * widget,
  cairo_t * cr,
  void * data);

void gtk_run(
  gtk_draw_event_function draw_event,
  void * a,
  double width,
  double height,
  int speed,
  const char * title);

#endif /* _gtk_run_h */