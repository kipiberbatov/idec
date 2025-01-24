#include <dlfcn.h>

#include "color.h"
#include "idec_animation.h"
#include "idec_command_line.h"
#include "idec_filled_window.h"

int main(int argc, char ** argv)
{
  char * animation_backend, * animation_library, * canvas_backend,
       * canvas_library, * output_name = NULL;
  int size, status;
  const int close_automatically_default = 0, timelapse_default = 100,
            total_colors_default = 100;
  const double height_default = 500,  width_default = 500;
  struct idec_filled_window fill;
  struct idec_animation animation;

  extern const struct idec_animation_intrinsic_functions *
  idec_filled_window_intrinsic_functions;

  idec_command_line option_animation_backend, option_animation_library,
                    option_canvas_backend, option_canvas_library,
                    option_close_automatically, option_height, option_output,
                    option_timelapse, option_title, option_total_colors,
                    option_width, no_positional_arguments;

  idec_command_line *(options[]) =
  {
    &option_animation_library,
    &option_animation_backend,
    &option_canvas_library,
    &option_canvas_backend,
    &option_total_colors,
    &option_width,
    &option_height,
    &option_output,
    &option_title,
    &option_timelapse,
    &option_close_automatically,
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
    &option_output, &output_name, "--output", NULL);
  option_output.minimal_number_of_arguments = 0;

  idec_command_line_set_option_string(
    &option_title, &(animation.title), "--title", "Changing colors");

  idec_command_line_set_option_int(
    &option_total_colors, &(fill.total_colors), "--total-colors",
    &total_colors_default);

  idec_command_line_set_option_int(
    &option_timelapse, &(animation.timelapse),
    "--timelapse", &timelapse_default);

  idec_command_line_set_option_double(
    &option_width, &(fill.width), "--width", &width_default);

  idec_command_line_set_option_double(
    &option_height, &(fill.height), "--height", &height_default);

  idec_command_line_set_option_int(
    &option_close_automatically, &(animation.close_automatically),
    "--close-automatically", &close_automatically_default);

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

  fill.new_index = 0;
  animation.data = (void *) &fill;
  animation.total_colors = fill.total_colors;
  animation.intrinsic_functions = idec_filled_window_intrinsic_functions;

  idec_animation_check_input(&status, &animation);
  if (status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("bad input\n", stderr);
    goto end;
  }

  idec_animation_read_and_apply_backends(
    &animation, &status,
    argc, argv, output_name,
    canvas_library, canvas_backend, animation_library, animation_backend);
  if (status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot read and apply backends\n", stderr);
    goto end;
  }

end:
  return status;
}
