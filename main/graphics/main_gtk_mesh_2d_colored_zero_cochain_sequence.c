#include <alloca.h>
#include <errno.h>
#include <stdlib.h>

#include <gtk/gtk.h>

#include "double.h"
#include "graphics_log.h"
#include "frame.h"
#include "int.h"
#include "mesh.h"
#include "mesh_2d_colored_zero_cochain_sequence.h"
#include "paint_rgb.h"
#include "gtk_draw.h"
#include "gtk_run.h"

static int gtk_draw_zero_cochain(GtkWidget * widget, cairo_t * cr, void * data)
{
  gtk_draw(
    widget,
    cr,
    data,
    mesh_2d_colored_zero_cochain_sequence_snapshot_cairo_draw_void,
    mesh_2d_colored_zero_cochain_sequence_get_index_void,
    mesh_2d_colored_zero_cochain_sequence_get_total_steps_void,
    mesh_2d_colored_zero_cochain_sequence_increment_index_void
  );
  return FALSE;
}

int main(int argc, char ** argv)
{
  char * m_format, * u_format;
  char * m_filename, * u_filename;
  int i, n, steps, total_colors;
  unsigned int speed;
  double height, width;
  double * new_coordinates, * u;
  mesh * m;
  mesh_2d_colored_zero_cochain_sequence a;
  char * title;
  margin window_margin;
  frame_mesh_data data;
  frame window_frame;
  
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
  
  i = 0;
  
  m_format = argv[1];
  m_filename = argv[2];
  m = mesh_file_scan_by_name(m_filename, m_format);
  if (errno)
  {
    fprintf(stderr,
      "Error during execution of function %s in file %s on line %d: "
      "could not generate input mesh\n",
      __func__, __FILE__,__LINE__);
    goto end;
  }
  
  steps = int_string_scan(argv[3]);
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
  u = double_matrix_file_scan_by_name(u_filename, n, m->cn[0], u_format);
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
  window_margin.left = 50;
  window_margin.right = 50;
  window_margin.top = 50;
  window_margin.bottom = 50;
  data.coordinates = new_coordinates;
  frame_internal_info_for_set_of_points(
    &window_frame,
    &data,
    m->cn[0],
    m->coord,
    width,
    height,
    &window_margin);
  fprintf(stderr, "point_size = %g\n", data.point_size);

  total_colors = 1000;
  
  a.index = i;
  a.total_steps = n;
  a.m = m;
  a.values = u;
  
  a.total_colors = total_colors;
  a.new_coordinates = new_coordinates;
  // double_matrix_file_print(stderr, m->cn[0], 2, new_coordinates, "--raw");
  if (data.point_size >= 5)
    a.point_size = data.point_size;
  else
    a.point_size = 5;
  a.min_value = double_array_min(n * m->cn[0], u);
  a.max_value = double_array_max(n * m->cn[0], u);
  fprintf(stderr, "min = %g, max = %g\n", a.min_value, a.max_value);
  a.paint = paint_rgb;
  
  speed = 100;
  title = "Heat flow in 2D";
  
  gtk_init(&argc, &argv);
  
  gtk_run(gtk_draw_zero_cochain, (void *) &a, width, height, speed, title);
  
  gtk_main();

  graphics_log(stdout, argc, argv);
  printf("Iterations from i = 0 to i = %d were executed\n", a.index);
  printf("Total range of iterations: i = 0 to i = %d\n", steps);
  
  errno = 0;
  
  free(new_coordinates);
u_free:
  free(u);
m_free:
  mesh_free(m);
end:
  return errno;
}
