#include <cairo.h>
#include <gtk/gtk.h>

#include "context_fill.h"

static void do_drawing(GtkWidget * widget, cairo_t * cr, int * i, int n)
{
  int height, width;
  GtkWidget * win;
  
  win = gtk_widget_get_toplevel(widget);
  gtk_window_get_size(GTK_WINDOW(win), &width, &height);
  context_fill(cr, width, height, *i, n);
  if (*i < n - 1)
    *i += 1;
}

typedef struct
{
  int i;
  int n;
} color;

static int on_draw_event(GtkWidget * widget, cairo_t * cr, void * user_data)
{
  color * a = (color *) user_data;
  
  do_drawing(widget, cr, &(a->i), a->n);
  return FALSE;
}

static int time_handler(GtkWidget * widget)
{
  gtk_widget_queue_draw(widget);
  return TRUE;
}

int main(int argc, char * argv[])
{
  color a = {.i = 0, .n = 100};
  GtkWidget * window;
  GtkWidget * drawing_area;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  drawing_area = gtk_drawing_area_new();
  gtk_container_add(GTK_CONTAINER (window), drawing_area);

  g_signal_connect(G_OBJECT(drawing_area), "draw",
                   G_CALLBACK(on_draw_event), &a);
  g_signal_connect(G_OBJECT(window), "destroy",
                   G_CALLBACK(gtk_main_quit), NULL);
 
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
  gtk_window_set_title(GTK_WINDOW(window), "Changing colors");

  g_timeout_add(50, (GSourceFunc) time_handler, (void *) window);

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}
