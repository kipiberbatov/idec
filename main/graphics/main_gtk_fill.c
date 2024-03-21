#include <alloca.h>

#include <gtk/gtk.h>

#include "fill.h"
#include "paint_rgb.h"
#include "gtk_draw.h"
#include "gtk_time_handler.h"

static int gtk_draw_fill(GtkWidget * widget, cairo_t * cr, void * data)
{
  gtk_draw(
    widget,
    cr,
    data,
    fill_draw_void,
    fill_get_index_void,
    fill_get_total_steps_void
  );
  return FALSE;
}

int main(int argc, char * argv[])
{
  int begin, n, total_colors;
  int * i;
  unsigned int speed;
  double height, width;
  fill * a;
  GtkWidget * window;
  GtkWidget * drawing_area;
  
  begin = 0;
  i = &begin;
  n = 100;
  total_colors = n;
  
  a = (fill *) alloca(fill_size());
  fill_set(a, i, n, total_colors, paint_rgb);
  
  width = 500;
  height = 500;
  speed = 100;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  drawing_area = gtk_drawing_area_new();
  gtk_container_add(GTK_CONTAINER (window), drawing_area);

  g_signal_connect(G_OBJECT(drawing_area), "draw",
                   G_CALLBACK(gtk_draw_fill), a);
  g_signal_connect(G_OBJECT(window), "destroy",
                   G_CALLBACK(gtk_main_quit), NULL);
 
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), width, height);
  gtk_window_set_title(GTK_WINDOW(window), "Changing colors");

  g_timeout_add(speed, (GSourceFunc) gtk_time_handler, (void *) window);

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}
