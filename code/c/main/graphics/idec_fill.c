#include <dlfcn.h>

#include "color.h"
#include "idec_animation.h"
#include "idec_command_line.h"
#include "paint_rgb.h"

struct idec_fill
{
  int width;
  int height;
  int old_index;
  int new_index;
  int total_colors;
};

static double get_width(const void * animation)
{
  return ((struct idec_fill *) animation)->width;
}

static double get_height(const void * animation)
{
  return ((struct idec_fill *) animation)->height;
}

static int get_total_steps(const void * animation)
{
  return ((struct idec_fill *) animation)->total_colors;
}

static int * get_old_index_address(const void * animation)
{
  return &(((struct idec_fill *) animation)->old_index);
}

static int * get_new_index_address(const void * animation)
{
  return &(((struct idec_fill *) animation)->new_index);
}

static void update_new_index(void * animation)
{
  ((struct idec_fill *) animation)->new_index += 1;
}

const struct idec_animation_intrinsic_functions
idec_fill_intrinsic_functions =
{
  get_width,
  get_height,
  get_total_steps,
  get_old_index_address,
  get_new_index_address,
  update_new_index
};

static void set_background_color(void * canvas)
{
  cairo_set_source_rgb((cairo_t *) canvas, 1, 1, 1);
}

static void draw(
  void * canvas, int * status, const void * data, int total_colors,
  void (*scheme)(void *, int *, int, int))
{
  cairo_t * cr = (cairo_t *) canvas;
  struct idec_fill * object = (struct idec_fill *) data;

  scheme(canvas, status, object->new_index, object->total_colors);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot apply color scheme\n", stderr);
    return;
  }
  cairo_paint(cr);
}

const struct idec_animation_canvas_functions
idec_fill_canvas_functions =
{
  set_background_color,
  (void (*)(void *, int *, int, int)) paint_rgb,
  draw
};

int main(int argc, char ** argv)
{
  void * lib_handle;
  char * animation_backend, * animation_library, * error, * output_name = NULL;
  int size, status;
  const int close_automatically_default = 0, timelapse_default = 100,
            total_colors_default = 100;
  double height, width;
  const double height_default = 500,  width_default = 500;
  struct idec_fill fill;
  struct idec_animation animation;
  idec_animation_backend_t * animator;

  idec_command_line option_animation_backend, option_animation_library,
                    option_close_automatically, option_height, option_output,
                    option_timelapse, option_title, option_total_colors,
                    option_width, no_positional_arguments;

  idec_command_line *(options[]) =
  {
    &option_animation_library,
    &option_animation_backend,
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
    return status;
  }

  if (fill.total_colors < 1)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "the number of colors is %s%d%s but it must be positive\n",
      color_variable, fill.total_colors, color_none);
    status = 1;
    return status;
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
  animation.intrinsic_functions = &idec_fill_intrinsic_functions;
  animation.canvas_functions = &idec_fill_canvas_functions;
  animation.total_colors = fill.total_colors;

  lib_handle = dlopen(animation_library, RTLD_LAZY);
  error = dlerror();
  if (error)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "%s\n", error);
    status = 1;
    return status;
  }

  *(void **) (&animator) = dlsym(lib_handle, animation_backend);
  error = dlerror();
  if (error)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "%s\n", error);
    status = 1;
    goto lib_close;
  }

  animator(&animation, &status, argc, argv, output_name);
  if (status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot draw animation\n", stderr);
    goto lib_close;
  }

lib_close:
  dlclose(lib_handle);
  return status;
}
