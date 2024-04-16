#include "gtk_run.h"
#include "gtk_time_handler.h"

void gtk_run(
  int (*draw_event)(GtkWidget *, cairo_t * cr, void *),
  void * a,
  double width,
  double height,
  int speed,
  const char * title)
{
  GtkWidget * window, * drawing_area;
  
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  drawing_area = gtk_drawing_area_new();
  gtk_container_add(GTK_CONTAINER (window), drawing_area);

  g_signal_connect(G_OBJECT(drawing_area), "draw",
                   G_CALLBACK(draw_event), a);
  g_signal_connect(G_OBJECT(window), "destroy",
                   G_CALLBACK(gtk_main_quit), NULL);
 
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), width, height);
  gtk_window_set_title(GTK_WINDOW(window), title);

  g_timeout_add(speed, (GSourceFunc) gtk_time_handler, (void *) window);

  gtk_widget_show_all(window);
}
