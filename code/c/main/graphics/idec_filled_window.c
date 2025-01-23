#include <dlfcn.h>

#include "color.h"
#include "idec_animation.h"
#include "idec_command_line.h"
#include "idec_filled_window.h"

int main(int argc, char ** argv)
{
  void * lib_animation, * lib_canvas;
  char * animation_backend, * animation_library, * canvas_backend,
       * canvas_library, * error, * output_name = NULL;
  int size, status;
  const int close_automatically_default = 0, timelapse_default = 100,
            total_colors_default = 100;
  double height, width;
  const double height_default = 500,  width_default = 500;
  struct idec_filled_window fill;
  struct idec_animation animation;
  idec_animation_backend_t * animator;

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
    &option_width, &(width), "--width", &width_default);

  idec_command_line_set_option_double(
    &option_height, &(height), "--height", &height_default);

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

  if (fill.total_colors < 1)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "the number of colors is %s%d%s but it must be positive\n",
      color_variable, fill.total_colors, color_none);
    status = 1;
    goto end;
  }

  if (animation.timelapse <= 0)
  {
    fprintf(stderr,
      "%sWarning:%s timelapse = %s%d%s but it should be positive.\n"
      "timelapse = 1 will be used instead.\n",
      color_red, color_none,
      color_variable, animation.timelapse, color_none);
    animation.timelapse = 1;
  }

  fill.width = (int) width;
  fill.height = (int) height;
  fill.new_index = 0;
  animation.data = (void *) &fill;
  animation.total_colors = fill.total_colors;
  animation.intrinsic_functions = idec_filled_window_intrinsic_functions;

  lib_canvas = dlopen(canvas_library, RTLD_LAZY);
  error = dlerror();
  if (error)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "%s\n", error);
    status = 1;
    goto end;
  }

  *(void **) &(animation.canvas_functions) = dlsym(lib_canvas, canvas_backend);
  error = dlerror();
  if (error)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "%s\n", error);
    status = 1;
    goto lib_canvas_close;
  }

  lib_animation = dlopen(animation_library, RTLD_LAZY);
  error = dlerror();
  if (error)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "%s\n", error);
    status = 1;
    goto lib_canvas_close;
  }

  *(void **) (&animator) = dlsym(lib_animation, animation_backend);
  error = dlerror();
  if (error)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "%s\n", error);
    status = 1;
    goto lib_animation_close;
  }

  animator(&animation, &status, argc, argv, output_name);
  if (status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot draw animation\n", stderr);
    goto lib_animation_close;
  }

lib_animation_close:
  dlclose(lib_animation);
lib_canvas_close:
  dlclose(lib_canvas);
end:
  return status;
}
