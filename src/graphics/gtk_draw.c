#include <stdio.h>
#include "gtk_draw.h"

void gtk_draw(
  GtkWidget * widget,
  cairo_t * cr,
  void * a,
  drawer draw,
  get_index_t get_index,
  get_total_steps_t get_total_steps)
{
  int height, n, width;
  int * i;
  GtkWidget * window;

  window = gtk_widget_get_toplevel(widget);
  gtk_window_get_size(GTK_WINDOW(window), &width, &height);
  draw(cr, width, height, a);
  i = get_index(a);
  n = get_total_steps(a);
  fprintf(stderr, "i = %d\n", *i);
  if (*i < n - 1)
    *i += 1;
}
