#include <errno.h>
#include <stdlib.h>

#include <gtk/gtk.h>

#include "color.h"
#include "double.h"
#include "graphics_log.h"
#include "frame.h"
#include "idec_command_line.h"
#include "idec_error_message.h"
#include "int.h"
#include "mesh.h"
#include "mesh_2d_colored_zero_cochain_sequence.h"
#include "paint_rgb.h"
#include "gtk_draw.h"
#include "gtk_run.h"

static int gtk_draw_zero_cochain(GtkWidget * widget, cairo_t * cr, void * data)
{
  int status = 0;
  gtk_draw(
    widget,
    cr,
    data,
    &status,
    mesh_2d_colored_zero_cochain_sequence_snapshot_cairo_draw_void,
    mesh_2d_colored_zero_cochain_sequence_get_index_void,
    mesh_2d_colored_zero_cochain_sequence_get_total_steps_void,
    mesh_2d_colored_zero_cochain_sequence_increment_index_void
  );
  return FALSE;
}

int main(int argc, char ** argv)
{
  char * m_format, * m_name, * title, * u_format, * u_name;
  int n, number_of_steps, size, status, timelapse, total_colors;
  const int timelapse_default = 100, total_colors_default = 1000;
  double coefficient_left, coefficient_right, coefficient_bottom,
         coefficient_top, height, width;
  const double coefficient_bottom_default = 0.1,
               coefficient_left_default = 0.1,
               coefficient_right_default = 0.1,
               coefficient_top_default = 0.1,
               height_default = 500,
               width_default = 500;
  double * new_coordinates, * u;
  mesh * m;
  mesh_2d_colored_zero_cochain_sequence a;
  margin window_margin;
  frame_mesh_data data;

  idec_command_line option_cochain_0_values, option_cochain_0_format,
                    option_coefficient_bottom, option_coefficient_left,
                    option_coefficient_right, option_coefficient_top,
                    option_height, option_mesh, option_mesh_format,
                    option_numner_of_steps, option_timelapse,
                    option_total_colors, option_title, option_width,
                    no_positional_argument;

  idec_command_line *(options[]) =
  {
    &option_mesh,
    &option_mesh_format,
    &option_numner_of_steps,
    &option_cochain_0_format,
    &option_cochain_0_values,
    &option_title,
    &option_total_colors,
    &option_timelapse,
    &option_width,
    &option_height,
    &option_coefficient_left,
    &option_coefficient_right,
    &option_coefficient_top,
    &option_coefficient_bottom,
    &no_positional_argument
  };

  idec_command_line_set_option_string(
    &option_mesh_format, &m_format, "--mesh-format", "--raw");

  idec_command_line_set_option_string(&option_mesh, &m_name, "--mesh", NULL);

  idec_command_line_set_option_int(
    &option_numner_of_steps, &number_of_steps, "--number-of-steps", NULL);

  idec_command_line_set_option_string(
    &option_cochain_0_format, &u_format, "--cochain-0-format", "--raw");

  idec_command_line_set_option_string(
    &option_cochain_0_values, &u_name, "--cochain-0", NULL);

  idec_command_line_set_option_string(&option_title, &title, "--title", NULL);

  idec_command_line_set_option_string(&option_mesh, &m_name, "--mesh", NULL);

  idec_command_line_set_option_int(
    &option_total_colors, &total_colors, "--total-colors",
    &total_colors_default);

  idec_command_line_set_option_int(
    &option_timelapse, &timelapse, "--timelapse", &timelapse_default);

  idec_command_line_set_option_double(
    &option_width, &width, "--width", &width_default);

  idec_command_line_set_option_double(
    &option_height, &height, "--height", &height_default);

  idec_command_line_set_option_double(
    &option_coefficient_left, &coefficient_left,
    "--margin-percentage-left", &coefficient_left_default);

  idec_command_line_set_option_double(
    &option_coefficient_right, &coefficient_right,
    "--margin-percentage-right", &coefficient_right_default);

  idec_command_line_set_option_double(
    &option_coefficient_top, &coefficient_top,
    "--margin-percentage-top", &coefficient_top_default);

  idec_command_line_set_option_double(
    &option_coefficient_bottom, &coefficient_bottom,
    "--margin-percentage-bottom", &coefficient_bottom_default);

  idec_command_line_set_option_no_arguments(
    &no_positional_argument, NULL, NULL, NULL);

  size = (int) (sizeof(options) / sizeof(*options));
  status = 0;
  idec_command_line_parse(options, &status, size, argc, argv);
  if (status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot parse command line options\n", stderr);
    return status;
  }

  errno = 0;

  if (number_of_steps < 0)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "the number of steps is %d but it must be at least 0\n", number_of_steps);
    return 1;
  }
  n = number_of_steps + 1;

  m = mesh_file_scan_by_name(m_name, m_format);
  if (m == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan mesh m from file %s in format %s\n", m_name, m_format);
    goto end;
  }

  u = double_matrix_file_scan_by_name(u_name, n, m->cn[0], u_format);
  if (u == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan cochain sequence u from file %s in format %s\n",
      u_name, u_format);
    goto m_free;
  }

  new_coordinates = (double *) malloc(sizeof(double) * 2 * m->cn[0]);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    idec_error_message_malloc(sizeof(double) * 2 * m->cn[0], "new_coordinates");
    goto u_free;
  }

  window_margin.left = width * coefficient_left;
  window_margin.right = width * coefficient_right;
  window_margin.top = height * coefficient_top;
  window_margin.bottom = height * coefficient_bottom;
  data.coordinates = new_coordinates;
  frame_internal_info_for_set_of_points(
    &data,
    m->cn[0],
    m->coord,
    width,
    height,
    &window_margin);
  fprintf(stderr, "point_size = %g\n", data.point_size);

  a.index = 0;
  a.total_steps = n;
  a.m = m;
  a.values = u;

  a.total_colors = total_colors;
  a.new_coordinates = new_coordinates;
  if (data.point_size >= 5)
    a.point_size = data.point_size;
  else
    a.point_size = 5;
  a.min_value = double_array_min(n * m->cn[0], u);
  a.max_value = double_array_max(n * m->cn[0], u);
  fprintf(stderr, "min = %g, max = %g\n", a.min_value, a.max_value);
  a.paint = paint_rgb;

  gtk_init(&argc, &argv);

  gtk_run(gtk_draw_zero_cochain, (void *) &a, width, height, timelapse, title);

  gtk_main();

  graphics_log(stdout, argc, argv);
  printf("Iterations from i = 0 to i = %d were executed\n", a.index);
  printf("Total range of iterations: i = 0 to i = %d\n", number_of_steps);

  errno = 0;

  free(new_coordinates);
u_free:
  free(u);
m_free:
  mesh_free(m);
end:
  return errno;
}
