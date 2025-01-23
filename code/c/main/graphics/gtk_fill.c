#include <stdio.h>

#include <gtk/gtk.h>

#include "color.h"
#include "fill.h"
#include "graphics_log.h"
#include "gtk_draw.h"
#include "gtk_run.h"
#include "idec_command_line.h"
// #include "int.h"
#include "paint_rgb.h"

struct fill
{
  int old_index;
  int new_index;
  int total_colors;
  painter paint;
};

typedef struct
{
  GtkWidget * drawing_area;
  struct fill * object;
  int close_automatically;
  int status;
  int to_be_closed;
  int id;
} AppData;

static int on_timeout(AppData * data)
{
  if (data->object->new_index >= data->object->total_colors)
  {
    if (data->close_automatically)
      data->to_be_closed = 1;
    else
      fputs("Application has reached its end. You should close the window\n",
        stderr);
    g_source_remove(data->id);
    return FALSE;
  }
  gtk_widget_queue_draw(data->drawing_area);
  return TRUE;
}

static int my_draw_event(
  GtkWidget * widget,
  cairo_t * cr,
  AppData * data)
{
  struct fill * a;

  a = data->object;
  if (a->new_index >= a->total_colors)
  {
    a->paint(cr, &(data->status), a->old_index, a->total_colors);
    if (data->status)
    {
      color_error_position(__FILE__, __LINE__);
      fputs("cannot draw to Cairo context\n", stderr);
      data->to_be_closed = 1;
      return TRUE;
    }
    cairo_paint(cr);
    return TRUE;
  }
  a->paint(cr, &(data->status), a->new_index, a->total_colors);
  if (data->status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot draw to Cairo context\n", stderr);
    data->to_be_closed = 1;
    return TRUE;
  }
  cairo_paint(cr);
  a->old_index = a->new_index;
  fprintf(stderr, "i = %d\n", a->old_index);
  a->new_index += 7;
  return TRUE;
}

static void on_window_destroy(GtkWidget *widget, int * status)
{
  *status = 1;
}

int main(int argc, char ** argv)
{
  char * title;
  int size, status, timelapse;
  const int close_automatically_default = 0, timelapse_default = 100,
            total_colors_default = 100;
  double height, width;
  const double height_default = 500,  width_default = 500;
  fill a;
  GtkWidget * window;
  AppData data;

  idec_command_line option_close_automatically, option_height, option_timelapse,
                    option_title, option_total_colors, option_width,
                    no_positional_arguments;

  idec_command_line *(options[]) =
  {
    &option_title,
    &option_total_colors,
    &option_timelapse,
    &option_width,
    &option_height,
    &option_close_automatically,
    &no_positional_arguments
  };

  idec_command_line_set_option_string(
    &option_title, &title, "--title", "Changing colors");

  idec_command_line_set_option_int(
    &option_total_colors, &(a.total_colors), "--total-colors",
    &total_colors_default);

  idec_command_line_set_option_int(
    &option_timelapse, &timelapse, "--timelapse", &timelapse_default);

  idec_command_line_set_option_double(
    &option_width, &width, "--width", &width_default);

  idec_command_line_set_option_double(
    &option_height, &height, "--height", &height_default);

  idec_command_line_set_option_int(
    &option_close_automatically, &(data.close_automatically),
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

  if (a.total_colors < 1)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "the number of colors is %s%d%s but it must be positive\n",
      color_variable, a.total_colors, color_none);
    status = 1;
    return status;
  }

  if (timelapse <= 0)
  {
    fprintf(stderr,
      "%sWarning:%s timelapse = %s%d%s but it should be positive.\n"
      "timelapse = 1 will be used instead.\n",
      color_red, color_none,
      color_variable, timelapse, color_none);
    timelapse = 1;
  }

  a.new_index = 0;
  a.paint = paint_rgb;

  gtk_init(NULL, NULL);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  data.drawing_area = gtk_drawing_area_new();
  gtk_container_add(GTK_CONTAINER (window), data.drawing_area);

  data.object = &a;
  data.status = 0;
  data.to_be_closed = 0;

  g_signal_connect(G_OBJECT(data.drawing_area), "draw",
                   G_CALLBACK(my_draw_event), &data);
  g_signal_connect(G_OBJECT(window), "destroy",
                   G_CALLBACK(on_window_destroy), &(data.to_be_closed));

  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), width, height);
  gtk_window_set_title(GTK_WINDOW(window), title);

  data.id = g_timeout_add(timelapse, (GSourceFunc) on_timeout, (void *) &data);

  gtk_widget_show_all(window);

  while (!data.to_be_closed)
    gtk_main_iteration_do(FALSE);

  graphics_log(stdout, argc, argv);
  if (a.new_index == 0)
    puts("No iterations were executed");
  else
  {
    printf("Iterations from i = 0 to i = %d were executed\n", a.old_index);
    printf("Total range of iterations: i = 0 to i = %d\n", a.total_colors - 1);
  }

  return data.status;
}
