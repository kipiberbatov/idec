#include <alloca.h>
#include <stdio.h>
#include <time.h>

#include <gtk/gtk.h>

#include "color.h"
#include "fill.h"
#include "graphics_log.h"
#include "gtk_draw.h"
#include "gtk_run.h"
#include "idec_error_message.h"
#include "int.h"
#include "paint_rgb.h"

static int gtk_draw_fill(GtkWidget * widget, cairo_t * cr, void * data)
{
  gtk_draw(
    widget,
    cr,
    data,
    fill_draw_void,
    fill_get_index_void,
    fill_get_total_steps_void,
    fill_increment_index_void
  );
  return FALSE;
}

int main(int argc, char ** argv)
{
  int i, n;
  unsigned int speed;
  double height, width;
  fill * a;
  char * title;

  errno = 0;

#define ARGC 2
  if (argc != ARGC)
  {
    color_error_position(__FILE__, __LINE__);
    idec_error_message_number_of_command_line_arguments_mismatch(ARGC, argc);
    errno = EINVAL;
    return errno;
  }

  i = 0;
  n = int_string_scan(argv[1]);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan number of colors from string %s\n", argv[1]);
    return errno;
  }
  if (n < 1)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "the number of colors is %d but it must be at least 1\n", n);
    return errno;
  }

  a = (fill *) alloca(fill_size());
  fill_set(a, i, n, paint_rgb);

  width = 500;
  height = 500;
  speed = 100;
  title = "Changing colors";

  gtk_init(&argc, &argv);

  gtk_run(gtk_draw_fill, (void *) a, width, height, speed, title);

  gtk_main();

  errno = 0;

  graphics_log(stdout, argc, argv);
  i = fill_get_index_void((void *) a);
  printf("Iterations from i = 0 to i = %d were executed\n", i);
  printf("Total range of iterations: i = 0 to i = %d\n", n);

  return errno;
}
