#include <alloca.h>
#include <errno.h>
#include <stdlib.h>

#include <gtk/gtk.h>

#include "double.h"
#include "diffusion.h"
// #include "gtk_spacetime_pde.h"
#include "image.h"
#include "int.h"
#include "mesh.h"
#include "rgb.h"

static void do_drawing(GtkWidget * widget, cairo_t * cr, diffusion * a)
{
  int height, n, width;
  int * i;
  GtkWidget * window;

  window = gtk_widget_get_toplevel(widget);
  gtk_window_get_size(GTK_WINDOW(window), &width, &height);
  // gtk_spacetime_pde(cr, width, height, a);
  diffusion_draw_snapshot(cr, width, height, a);
  i = diffusion_get_index(a);
  n = diffusion_total_steps(a);
  fprintf(stderr, "i = %d\n", *i);
  if (*i < n - 1)
    *i += 1;
}

static int on_draw_event(GtkWidget * widget, cairo_t * cr, void * user_data)
{
  do_drawing(widget, cr, (diffusion *) user_data);
  return FALSE;
}

static int time_handler(GtkWidget * widget)
{
  gtk_widget_queue_draw(widget);
  return TRUE;
}

static void painter(cairo_t * cr, int ind, int total_colors)
{
  rgb color;
  rgb_color(&color, ind, total_colors);
  cairo_set_source_rgb(cr, color.red, color.green, color.blue);
}

int main(int argc, char * argv[])
{
  char * m_format, * u_format;
  char * m_filename, * u_filename;
  int begin, n, steps, total_colors;
  int * i;
  unsigned int speed;
  double height, point_size, width;
  double * new_coordinates, * u;
  mesh * m;
  diffusion * a;
  GtkWidget * window;
  GtkWidget * drawing_area;
  
  errno = 0;
  
  if (argc != 6)
  {
    fprintf(stderr, 
      "Error during execution of function %s in file %s on line %d: "
      "number of command-line arguments must be 6\n",
      __func__, __FILE__,__LINE__);
    errno = EINVAL;
    goto end;
  }
  
  begin = 0;
  i = &begin;
  
  m_format = argv[1];
  m_filename = argv[2];
  m = mesh_fscan_by_name(m_filename, m_format);
  if (errno)
  {
    fprintf(stderr,
      "Error during execution of function %s in file %s on line %d: "
      "could not generate input mesh\n",
      __func__, __FILE__,__LINE__);
    goto end;
  }
  
  steps = int_sscan(argv[3]);
  if (errno)
  {
    fprintf(stderr,
      "Error during execution of function %s in file %s on line %d: "
      "unable to scan number of time steps\n",
       __func__, __FILE__,__LINE__);
    goto m_free;
  }
  n = steps + 1;
  
  u_format = argv[4];
  u_filename = argv[5];
  u = double_matrix_fscan_by_name(u_filename, n, m->cn[0], u_format);
  if (errno)
  {
    fprintf(stderr,
      "Error during execution of function %s in file %s on line %d: "
      "could not generate values\n",
       __func__, __FILE__,__LINE__);
    goto m_free;
  }
  
  new_coordinates = (double *) malloc(sizeof(double) * 2 * m->cn[0]);
  if (errno)
  {
    fprintf(stderr,
      "Error during execution of function %s in file %s on line %d: "
      "could not generate values\n",
       __func__, __FILE__,__LINE__);
    goto u_free;
  }
  
  width = 500;
  height = 500;
  image_new_coordinates(new_coordinates, m, width, height);
  point_size = image_point_size(width, height);
  
  total_colors = 1000;
  
  a = (diffusion *) alloca(diffusion_size());
  diffusion_set(a,
    i, n, m, new_coordinates, point_size, u, total_colors, painter);
  
  speed = 100;
  
  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  drawing_area = gtk_drawing_area_new();
  gtk_container_add(GTK_CONTAINER (window), drawing_area);

  g_signal_connect(G_OBJECT(drawing_area), "draw",
                   G_CALLBACK(on_draw_event), a);
  g_signal_connect(G_OBJECT(window), "destroy",
                   G_CALLBACK(gtk_main_quit), NULL);

  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), width, height);
  gtk_window_set_title(GTK_WINDOW(window), "Heat flow in 2D");

  g_timeout_add(speed, (GSourceFunc) time_handler, (void *) window);

  gtk_widget_show_all(window);
  gtk_main();
  errno = 0;
  
  free(new_coordinates);
u_free:
  free(u);
m_free:
  mesh_free(m);
end:
  return errno;
}
