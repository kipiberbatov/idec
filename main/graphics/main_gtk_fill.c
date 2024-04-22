#include <alloca.h>
#include <stdio.h>
#include <time.h>

#include <gtk/gtk.h>

#include "fill.h"
#include "graphics_log.h"
#include "gtk_draw.h"
#include "gtk_run.h"
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
  if (argc != 2)
  {
    fprintf(stderr, 
      "Error during execution of function %s in file %s on line %d: "
      "number of command-line arguments must be 2\n",
      __func__, __FILE__,__LINE__);
    errno = EINVAL;
    return errno;
  }

  i = 0;
  n = int_string_scan(argv[1]);
  if (errno)
  {
    fprintf(stderr,
      "Error during execution of function %s in file %s on line %d: "
      "unable to scan number of colors\n",
       __func__, __FILE__,__LINE__);
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

  graphics_log(stdout, argc, argv);
  i = fill_get_index_void((void *) a);
  printf("Iterations from i = 0 to i = %d were executed\n", i);
  printf("Total range of iterations: i = 0 to i = %d\n", n);

  return errno;
}
