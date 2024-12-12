#include <alloca.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <gtk/gtk.h>

#include "color.h"
#include "double.h"
#include "diffusion.h"
#include "frame.h"
#include "graphics_log.h"
#include "idec_error_message.h"
#include "int.h"
#include "mesh.h"
#include "paint_rgb.h"
#include "gtk_draw.h"
#include "gtk_run.h"

static int gtk_draw_diffusion(GtkWidget * widget, cairo_t * cr, void * data)
{
  gtk_draw(
    widget,
    cr,
    data,
    diffusion_draw_void,
    diffusion_get_index_void,
    diffusion_get_total_steps_void,
    diffusion_increment_index_void
  );
  return FALSE;
}

int main(int argc, char ** argv)
{
  char * m_format, * m_name, * u_name;
  int i, n, total_colors;
  unsigned int speed;
  double height, width;
  double * new_coordinates, * u;
  mesh * m;
  diffusion * a;
  const char title[80] = "Heat flow in 2D";
  FILE * in;
  int length;
  margin window_margin;
  frame_mesh_data data;

  errno = 0;

#define ARGC 4
  if (argc != ARGC)
  {
    color_error_position(__FILE__, __LINE__);
    idec_error_message_number_of_command_line_arguments_mismatch(ARGC, argc);
    errno = EINVAL;
    goto end;
  }

  i = 0;

  m_format = argv[1];
  m_name = argv[2];
  u_name = argv[3];

  m = mesh_file_scan_by_name(m_name, m_format);
  if (m == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan mesh m from file %s in format %s\n",
      m_name, m_format);
    goto end;
  }

  in = fopen(u_name, "r");
  if (in == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open array file %s in format for reading: %s\n",
      u_name, strerror(errno));
    goto m_free;
  }

  n = int_file_scan(in);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan n from file %s\n", u_name);
    fclose(in);
    goto m_free;
  }

  length = int_file_scan(in);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan length from file %s\n", u_name);
    fclose(in);
    goto m_free;
  }
  if (length != m->cn[0])
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "length = %d != %d = m->cn[0]\n", length, m->cn[0]);
    errno = EINVAL;
    goto m_free;
  }

  u = double_matrix_file_scan(in, n, m->cn[0], "--raw");
  if (u == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot scan u", stderr);
    fclose(in);
    goto u_free;
  }
  fclose(in);

  new_coordinates = (double *) malloc(sizeof(double) * 2 * m->cn[0]);
  if (new_coordinates == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    idec_error_message_malloc(sizeof(double) * 2 * m->cn[0], "new_coordinates");
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
    &data,
    m->cn[0],
    m->coord,
    width,
    height,
    &window_margin);

  total_colors = 10000;

  a = (diffusion *) alloca(diffusion_size());
  diffusion_set(a,
    i, n, m, new_coordinates, data.point_size, u, total_colors, paint_rgb);
  fprintf(stderr, "min = %g\nmax = %g\n",
    diffusion_min_value(a), diffusion_max_value(a));

  speed = 100;

  gtk_init(&argc, &argv);

  gtk_run(gtk_draw_diffusion, (void *) a, width, height, speed, title);

  gtk_main();

  graphics_log(stdout, argc, argv);
  printf("Iterations from i = 0 to i = %d were executed\n",
    diffusion_get_index(a));
  printf("Total range of iterations: i = 0 to i = %d\n",
    diffusion_get_total_steps(a));

  errno = 0;

  free(new_coordinates);
u_free:
  free(u);
m_free:
  mesh_free(m);
end:
  return errno;
}
