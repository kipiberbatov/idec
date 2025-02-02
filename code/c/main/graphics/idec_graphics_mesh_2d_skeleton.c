/* system headers */
#include <errno.h>
#include <stdlib.h>

/* internal headers */
#include "color.h"
#include "double.h"
#include "frame.h"
#include "idec_animation.h"
#include "idec_animation_generic_data.h"
#include "idec_command_line.h"
#include "idec_error_message.h"
#include "idec_graphics_mesh_2d_skeleton.h"
#include "mesh.h"

static void update_index(int * i){++*i;}

int main(int argc, char ** argv)
{
  char * animation_backend, * animation_library, * canvas_backend,
       * canvas_library, * m_format, * m_name, * output_name = NULL;
  int number_of_time_steps, size, status;
  const int close_automatically_default = 0, number_of_time_steps_default = 0,
            timelapse_default = 50, total_colors_default = 100;
  double coefficient_left, coefficient_right, coefficient_bottom,
         coefficient_top;
  const double coefficient_bottom_default = 0.1,
               coefficient_left_default = 0.1,
               coefficient_right_default = 0.1,
               coefficient_top_default = 0.1,
               height_default = 500,
               width_default = 500;
  double * new_coordinates;
  mesh * m;
  struct idec_graphics_mesh_2d_skeleton skeleton;
  struct idec_animation animation;
  struct idec_animation_generic_data generic_data;
  margin window_margin;
  frame_mesh_data data;

  idec_command_line option_animation_backend, option_animation_library,
                    option_canvas_backend, option_canvas_library,
                    option_close_automatically, option_coefficient_bottom,
                    option_coefficient_left, option_coefficient_right,
                    option_coefficient_top, option_height, option_mesh,
                    option_mesh_format, option_output, option_timelapse,
                    option_title, option_total_colors, option_total_steps,
                    option_width, no_positional_arguments;

  idec_command_line *(options[]) =
  {
    &option_animation_library,
    &option_animation_backend,
    &option_canvas_library,
    &option_canvas_backend,
    &option_mesh,
    &option_mesh_format,
    &option_width,
    &option_height,
    &option_title,
    &option_timelapse,
    &option_close_automatically,
    &option_total_steps,
    &option_total_colors,
    &option_output,
    &option_coefficient_left,
    &option_coefficient_right,
    &option_coefficient_top,
    &option_coefficient_bottom,
    &no_positional_arguments
  };

  idec_command_line_set_option_string(
    &option_animation_backend, &animation_backend, "--animation-backend", NULL);

  idec_command_line_set_option_string(
    &option_animation_library, &animation_library, "--animation-library", NULL);

  idec_command_line_set_option_string(
    &option_canvas_backend, &canvas_backend, "--canvas-backend", NULL);

  idec_command_line_set_option_string(
    &option_canvas_library, &canvas_library, "--canvas-library", NULL);

  idec_command_line_set_option_string(
    &option_mesh_format, &m_format, "--mesh-format", "--raw");

  idec_command_line_set_option_string(&option_mesh, &m_name, "--mesh", NULL);

  idec_command_line_set_option_double(
    &option_width, &(generic_data.width), "--width", &width_default);

  idec_command_line_set_option_double(
    &option_height, &(generic_data.height), "--height", &height_default);

  idec_command_line_set_option_int(
    &option_total_steps, &number_of_time_steps,
    "--number-of-time-steps", &number_of_time_steps_default);

  idec_command_line_set_option_int(
    &option_total_colors, &(animation.total_colors), "--total-colors",
    &total_colors_default);

  idec_command_line_set_option_int(
    &option_timelapse, &(animation.timelapse),
    "--timelapse", &timelapse_default);

  idec_command_line_set_option_string(
    &option_title, &(animation.title), "--title", "0-cochain sequence");

  idec_command_line_set_option_int(
    &option_close_automatically, &(animation.close_automatically),
    "--close-automatically", &close_automatically_default);

  idec_command_line_set_option_string(
    &option_output, &output_name, "--output", NULL);
  option_output.minimal_number_of_arguments = 0;

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

  idec_command_line_set_option_no_arguments(
    &no_positional_arguments, NULL, NULL, NULL);

  size = (int) (sizeof(options) / sizeof(*options));
  status = 0;
  idec_command_line_parse(options, &status, size, argc, argv);
  if (status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot parse command line options\n", stderr);
    goto end;
  }

  generic_data.total_steps = number_of_time_steps + 1;
  generic_data.new_index = 0;
  animation.generic_data = &generic_data;
  idec_animation_check_input(&status, &animation);
  if (status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("bad input\n", stderr);
    goto end;
  }

  errno = 0;

  m = mesh_file_scan_by_name(m_name, m_format);
  if (m == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan mesh m from file %s in format %s\n", m_name, m_format);
    status = 1;
    goto end;
  }

  new_coordinates = (double *) malloc(sizeof(double) * 2 * m->cn[0]);
  if (new_coordinates == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    idec_error_message_malloc(sizeof(double) * 2 * m->cn[0], "new_coordinates");
    status = 1;
    goto m_free;
  }

  window_margin.left = generic_data.width * coefficient_left;
  window_margin.right = generic_data.width * coefficient_right;
  window_margin.top = generic_data.height * coefficient_top;
  window_margin.bottom = generic_data.height * coefficient_bottom;
  data.coordinates = new_coordinates;
  frame_internal_info_for_set_of_points(
    &data,
    m->cn[0],
    m->coord,
    generic_data.width,
    generic_data.height,
    &window_margin);

  skeleton.m = m;
  skeleton.coordinates = new_coordinates;
  skeleton.line_width = data.line_width / 4;

  animation.data = (void *) &skeleton;
  animation.update_new_index = update_index;
  animation.draw_snapshot = idec_graphics_mesh_2d_skeleton_draw_snapshot;

  idec_animation_read_and_apply_backends(
    &animation, &status,
    argc, argv, output_name,
    canvas_library, canvas_backend, animation_library, animation_backend);
  if (status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot read and apply backends\n", stderr);
  }

  free(new_coordinates);
m_free:
  mesh_free(m);
end:
  return status;
}
