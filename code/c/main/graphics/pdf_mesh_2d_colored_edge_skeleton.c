/* system headers */
#include <errno.h>
#include <stdlib.h>
#include <string.h>

/* internal headers */
#include "color.h"
#include "double.h"
#include "frame.h"
#include "idec_command_line.h"
#include "idec_error_message.h"
#include "int.h"
#include "mesh.h"
#include "mesh_2d_colored_one_cochain_sequence.h"
#include "paint_rgb.h"
#include "pdf_write_to_file.h"

typedef void
draw_skeleton_t(cairo_t *, const struct mesh_2d_colored_one_cochain *);

static draw_skeleton_t * idec_mesh_draw_skeleton_get(const char * method)
{
  if (!strcmp(method, "default"))
    return mesh_2d_one_cochain_skeleton_draw;
  return NULL;
}

int main(int argc, char ** argv)
{
  char * m_format, * m_name, * method_draw_skeleton, * out_name;
  int size, status, total_colors;
  const int total_colors_default = 10;
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
  mesh_2d_colored_one_cochain_sequence a;
  margin window_margin;
  frame_mesh_data data;

  idec_command_line option_coefficient_bottom, option_coefficient_left,
                    option_coefficient_right, option_coefficient_top,
                    option_draw_skeleton,
                    option_height, option_mesh, option_mesh_format,
                    option_total_colors, option_width,
                    positional_argument_output;

  idec_command_line *(options[]) =
  {
    &option_mesh,
    &option_mesh_format,
    &option_width,
    &option_height,
    &option_total_colors,
    &option_coefficient_left,
    &option_coefficient_right,
    &option_coefficient_top,
    &option_coefficient_bottom,
    &option_draw_skeleton,
    &positional_argument_output
  };

  idec_command_line_set_option_string(
    &option_mesh_format, &m_format, "--mesh-format", "--raw");

  idec_command_line_set_option_string(&option_mesh, &m_name, "--mesh", NULL);

  idec_command_line_set_option_double(
    &option_width, &width, "--width", &width_default);

  idec_command_line_set_option_double(
    &option_height, &height, "--height", &height_default);

  idec_command_line_set_option_int(
    &option_total_colors, &total_colors, "--total-colors",
    &total_colors_default);

  idec_command_line_set_option_double(
    &option_coefficient_left, &coefficient_left,
    "--margin-percentage-left",
    &coefficient_left_default);

  idec_command_line_set_option_double(
    &option_coefficient_right, &coefficient_right,
    "--margin-percentage-right",
    &coefficient_right_default);

  idec_command_line_set_option_double(
    &option_coefficient_top, &coefficient_top,
    "--margin-percentage-top",
    &coefficient_top_default);

  idec_command_line_set_option_double(
    &option_coefficient_bottom, &coefficient_bottom,
    "--margin-percentage-bottom",
    &coefficient_bottom_default);

  idec_command_line_set_option_string(
    &option_draw_skeleton, &method_draw_skeleton,
    "--draw-skeleton", "default");

  idec_command_line_set_option_string(
    &positional_argument_output, &out_name, NULL, NULL);

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

  m = mesh_file_scan_by_name(m_name, m_format);
  if (m == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan mesh m from file %s%s%s in format %s%s%s\n",
      color_variable, m_name, color_none,
      color_variable, m_format, color_none);
    goto end;
  }

  u = (double *) calloc(m->cn[1], sizeof(double));
  if (u == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    idec_error_message_malloc(sizeof(double) * m->cn[1], "u");
    goto m_free;
  }

  new_coordinates = (double *) malloc(sizeof(double) * 2 * m->cn[0]);
  if (new_coordinates == NULL)
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

  a.is_mesh_edge_skeleton = 1;
  a.index = 0;
  a.total_steps = 1;
  a.m = m;
  a.bd_1 = NULL;
  a.values = u;

  a.total_colors = total_colors;
  a.new_coordinates = new_coordinates;
  a.point_size = -1;
  a.line_width = data.line_width;
  a.min_value = -1;
  a.max_value = 1;
  a.paint = paint_rgb;
  a.draw_skeleton = idec_mesh_draw_skeleton_get(method_draw_skeleton);
  if (a.draw_skeleton == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "method %s is not supported\n", method_draw_skeleton);
    errno = EINVAL;
    goto new_coordinates_free;
  }
  a.draw_values = NULL;

  pdf_write_to_file(
    out_name,
    width,
    height,
    (void *) &a,
    mesh_2d_colored_one_cochain_sequence_snapshot_cairo_draw_void,
    mesh_2d_colored_one_cochain_sequence_get_index_void,
    mesh_2d_colored_one_cochain_sequence_get_total_steps_void,
    mesh_2d_colored_one_cochain_sequence_increment_index_void);

new_coordinates_free:
  free(new_coordinates);
u_free:
  free(u);
m_free:
  mesh_free(m);
end:
  return errno;
}
