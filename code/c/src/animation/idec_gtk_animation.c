#include <errno.h>
#include <stdio.h>
#include <time.h>

#include <gtk/gtk.h>

#include "color.h"
#include "idec_animation.h"
#include "idec_animation_draw_snapshot.h"
#include "idec_animation_intrinsic_functions.h"

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
  void * data;
  int * (*get_old_index_address)(const void *);
  int * (*get_new_index_address)(const void *);
  void (*update_new_index)(void *);
  struct idec_animation * animation;

  animation = input->animation;
  data = animation->data;
  total_steps = animation->intrinsic_functions->get_total_steps(data);
  get_old_index_address = animation->intrinsic_functions->get_old_index_address;
  update_new_index = animation->intrinsic_functions->update_new_index;
  get_new_index_address = animation->intrinsic_functions->get_new_index_address;
  new_index = *(get_new_index_address(data));

  if (new_index >= total_steps)
  {
    *(get_new_index_address(data)) = *(get_old_index_address(data));
    idec_animation_draw_snapshot((void *) cr, animation, &(input->status));
    if (input->status)
    {
      color_error_position(__FILE__, __LINE__);
      fputs("cannot draw to Cairo context\n", stderr);
      input->to_be_closed = 1;
      return TRUE;
    }
    update_new_index(data);
    return TRUE;
  }
  idec_animation_draw_snapshot((void *) cr, animation, &(input->status));
  if (input->status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot draw to Cairo context\n", stderr);
    input->to_be_closed = 1;
    return TRUE;
  }
  fprintf(stderr, "i = %d\n", new_index);
  *(get_old_index_address(data)) = new_index;
  update_new_index(data);
  return TRUE;
}

static int on_timeout(struct idec_gtk_animation_input * input)
{
  int new_index, total_steps;
  void * data;
  int * (*get_new_index_address)(const void *);
  struct idec_animation * animation;

  animation = input->animation;
  data = animation->data;
  total_steps = animation->intrinsic_functions->get_total_steps(data);
  get_new_index_address = animation->intrinsic_functions->get_new_index_address;
  new_index = *(get_new_index_address(data));

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

  width = (int) animation->intrinsic_functions->get_width(animation->data);
  height = (int) animation->intrinsic_functions->get_height(animation->data);

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
  void * data;

  data = animation->data;
  total_steps = animation->intrinsic_functions->get_total_steps(data);

  idec_gtk_animation_run(animation, status);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot run GTK animation\n", stderr);
  }

  index = *(animation->intrinsic_functions->get_old_index_address(data));

  idec_gtk_animation_log_by_name(
    status, argc, argv, index, total_steps, output);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot log GTK animation\n", stderr);
  }
}
