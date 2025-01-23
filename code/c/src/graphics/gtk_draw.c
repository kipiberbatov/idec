#include <stdio.h>

#include "color.h"
#include "gtk_draw.h"

void gtk_draw(
  GtkWidget * widget,
  cairo_t * cr,
  void * a,
  int * status,
  void (*draw)(cairo_t *, int *, double, double, const void *),
  int (*get_index)(const void *),
  int (*get_total_steps)(const void *),
  void (*increment_index)(void *))
{
  int height, i, n, width;
  GtkWidget * window;

  window = gtk_widget_get_toplevel(widget);
  gtk_window_get_size(GTK_WINDOW(window), &width, &height);
  draw(cr, status, width, height, a);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot draw to Cairo context\n", stderr);
    return;
  }
  i = get_index(a);
  n = get_total_steps(a);
  fprintf(stderr, "i = %d\n", i);
  if (i < n - 1)
    increment_index(a);
}
