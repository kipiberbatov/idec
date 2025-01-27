#include <errno.h>
#include <stdio.h>
#include <time.h>

#include <gtk/gtk.h>

#include "color.h"
#include "idec_animation.h"
#include "idec_animation_canvas_functions.h"
#include "idec_animation_draw.h"
#include "idec_animation_generic_data.h"

struct idec_gtk_animation_input
{
  GtkWidget * drawing_area;
  struct idec_animation * animation;
  int status;
  int to_be_closed;
  int id;
};

static int on_draw_event(
  GtkWidget * widget,
  cairo_t * cr,
  struct idec_gtk_animation_input * input)
{
  int new_index, total_steps;
  struct idec_animation_generic_data * generic_data;
  struct idec_animation * animation;

  animation = input->animation;
  generic_data = animation->generic_data;
  total_steps = generic_data->total_steps;
  new_index = generic_data->new_index;

  if (new_index >= total_steps)
  {
    generic_data->new_index = generic_data->old_index;
    idec_animation_draw((void *) cr, animation, &(input->status));
    if (input->status)
    {
      color_error_position(__FILE__, __LINE__);
      fputs("cannot draw to Cairo context\n", stderr);
      input->to_be_closed = 1;
      return TRUE;
    }
    animation->update_new_index(&(generic_data->new_index));
    return TRUE;
  }
  idec_animation_draw((void *) cr, animation, &(input->status));
  if (input->status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot draw to Cairo context\n", stderr);
    input->to_be_closed = 1;
    return TRUE;
  }
  fprintf(stderr, "i = %d\n", new_index);
  generic_data->old_index = new_index;
  animation->update_new_index(&(generic_data->new_index));
  return TRUE;
}

static int on_timeout(struct idec_gtk_animation_input * input)
{
  int new_index, total_steps;
  struct idec_animation * animation;

  animation = input->animation;
  total_steps = animation->generic_data->total_steps;
  new_index = animation->generic_data->new_index;

  if (new_index >= total_steps)
  {
    if (animation->close_automatically)
      input->to_be_closed = 1;
    else
      fputs("Application has reached its end. You should close the window\n",
        stderr);
    g_source_remove(input->id);
    return FALSE;
  }
  gtk_widget_queue_draw(input->drawing_area);
  return TRUE;
}

static void on_window_destroy(GtkWidget *widget, int * to_be_closed)
{
  *to_be_closed = 1;
}

static void idec_gtk_animation_run(
  struct idec_animation * animation,
  int * status)
{
  int height, width;
  struct idec_gtk_animation_input input;
  GtkWidget * window;

  input.animation = animation;
  input.to_be_closed = 0;
  input.status = 0;

  width = (int) animation->generic_data->width;
  height = (int) animation->generic_data->height;

  gtk_init(NULL, NULL);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  input.drawing_area = gtk_drawing_area_new();
  gtk_container_add(GTK_CONTAINER (window), input.drawing_area);

  g_signal_connect(G_OBJECT(input.drawing_area), "draw",
                   G_CALLBACK(on_draw_event), &input);

  g_signal_connect(G_OBJECT(window), "destroy",
                   G_CALLBACK(on_window_destroy), &(input.to_be_closed));

  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), width, height);
  gtk_window_set_title(GTK_WINDOW(window), animation->title);

  input.id = g_timeout_add(
    animation->timelapse, (GSourceFunc) on_timeout, (void *) &input);

  gtk_widget_show_all(window);

  while (!input.to_be_closed)
    gtk_main_iteration_do(FALSE);
}

static void idec_program_log(FILE * out, int argc, char ** argv, int status)
{
  int i;
  time_t rawtime;
  struct tm * p;

  time(&rawtime);
  p = gmtime(&rawtime);

  fputs("The following command was run:\n", out);
  for (i = 0; i < argc - 1; ++i)
    fprintf(out, "%s ", argv[i]);
  fprintf(out, "%s\n", argv[i]);
  fprintf(out, "Program exited at %02d.%02d.%d %02d:%02d:%02d UTC\n",
    p->tm_mday, p->tm_mon + 1, p->tm_year + 1900,
    p->tm_hour, p->tm_min, p->tm_sec);
  fprintf(out, "Exit status: %d\n", status);
}

static void idec_gtk_animation_log(
  FILE * out, int argc, char ** argv, int index, int total_steps, int status)
{
  idec_program_log(out, argc, argv, status);
  fprintf(out, "Iterations from i = 0 to i = %d were executed\n", index);
  fprintf(out, "Total range of iterations: i = 0 to i = %d\n", total_steps - 1);
}

static void idec_gtk_animation_log_by_name(
  int * status, int argc, char ** argv, int index, int total_steps,
  const char * output)
{
  FILE * out;

  if (output == NULL)
  {
    idec_gtk_animation_log(stdout, argc, argv, index, total_steps, *status);
    return;
  }

  out = fopen(output, "w");
  if (out == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot open file %s%s%s: %s\n",
      color_variable, output, color_none,
      strerror(errno));
    *status = errno;
    return;
  }
  idec_gtk_animation_log(out, argc, argv, index, total_steps, *status);
  fclose(out);
}

void idec_gtk_animation(
  struct idec_animation * animation,
  int * status,
  int argc,
  char ** argv,
  const char * output)
{
  int index, total_steps;

  idec_gtk_animation_run(animation, status);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot run GTK animation\n", stderr);
  }

  total_steps = animation->generic_data->total_steps;
  index = animation->generic_data->old_index;

  idec_gtk_animation_log_by_name(
    status, argc, argv, index, total_steps, output);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot log GTK animation\n", stderr);
  }
}
