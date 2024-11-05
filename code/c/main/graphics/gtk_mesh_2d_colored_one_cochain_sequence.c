/* system headers */
#include <errno.h>
#include <stdlib.h>
#include <string.h>

/* external headers */
#include <gtk/gtk.h>

/* internal headers */
#include "color.h"
#include "double.h"
#include "graphics_log.h"
#include "gtk_draw.h"
#include "gtk_run.h"
#include "frame.h"
#include "int.h"
#include "mesh.h"
#include "mesh_2d_colored_one_cochain_sequence.h"
#include "paint_rgb.h"
#include "points_array_minimal_distance.h"

static int gtk_draw_one_cochain(GtkWidget * widget, cairo_t * cr, void * data)
{
  gtk_draw(
    widget,
    cr,
    data,
    mesh_2d_colored_one_cochain_sequence_snapshot_cairo_draw_void,
    mesh_2d_colored_one_cochain_sequence_get_index_void,
    mesh_2d_colored_one_cochain_sequence_get_total_steps_void,
    mesh_2d_colored_one_cochain_sequence_increment_index_void
  );
  return FALSE;
}

int main(int argc, char ** argv)
{
  char * m_format, * u_format;
  char * m_name, * u_filename;
  char * title;
  int i, n, steps, total_colors;
  unsigned int speed;
  double height, width;
  double * new_coordinates, * u;
  FILE * m_file;
  matrix_sparse * m_bd_1;
  mesh * m;
  mesh_2d_colored_one_cochain_sequence a;
  margin window_margin;
  frame_mesh_data data;
  frame window_frame;

  errno = 0;

  if (argc != 6)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "number of command-line arguments must be 6 instead it is %d\n", argc);
    errno = EINVAL;
    goto end;
  }

  i = 0;

  m_format = argv[1];
  m_name = argv[2];

  m_file = fopen(m_name, "r");
  if (m_file == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot open mesh file %s: %s\n", m_name, strerror(errno));
    goto end;
  }
  m = mesh_file_scan(m_file, m_format);
  if (m == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan mesh m from file %s in format %s\n",
      m_name, m_format);
    fclose(m_file);
    goto end;
  }

  m_bd_1 = mesh_file_scan_boundary_p(m_file, m, 1);
  if (m_bd_1 == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan m_bd_1 m from file %s\n", m_name);
    fclose(m_file);
    goto m_free;
  }
  fclose(m_file);

  steps = int_string_scan(argv[3]);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan number of time steps from string %s\n", argv[3]);
    goto m_bd_1_free;
  }
  n = steps + 1;

  u_format = argv[4];
  u_filename = argv[5];
  u = double_matrix_file_scan_by_name(u_filename, n, m->cn[1], u_format);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan sequence of cochain values\n");
    goto m_bd_1_free;
  }

  new_coordinates = (double *) malloc(sizeof(double) * 2 * m->cn[0]);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %ld bytes of memory for new_coordinate\n",
       sizeof(double) * 2 * m->cn[0]);
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

  total_colors = 1000;

  a.is_mesh_edge_skeleton = 0;
  a.index = i;
  a.total_steps = n;
  a.m = m;
  a.bd_1 = m_bd_1->values;
  a.values = u;

  a.total_colors = total_colors;
  a.new_coordinates = new_coordinates;
  a.point_size = points_array_minimal_distance(m->cn[0], new_coordinates);
  a.line_width = data.line_width;
  a.min_value = double_array_absolute_min(n * m->cn[1], u);
  a.max_value = double_array_absolute_max(n * m->cn[1], u);
  a.paint = paint_rgb;

  speed = 100;
  title = "Heat flux in 2D";

  gtk_init(&argc, &argv);

  gtk_run(gtk_draw_one_cochain, (void *) &a, width, height, speed, title);

  gtk_main();

  graphics_log(stdout, argc, argv);
  printf("Iterations from i = 0 to i = %d were executed\n", a.index);
  printf("Total range of iterations: i = 0 to i = %d\n", steps);

  errno = 0;

  free(new_coordinates);
u_free:
  free(u);
m_bd_1_free:
  matrix_sparse_free(m_bd_1);
m_free:
  mesh_free(m);
end:
  return errno;
}
