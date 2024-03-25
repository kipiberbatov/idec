#include <alloca.h>

#include <gtk/gtk.h>

#include "fill.h"
#include "paint_rgb.h"
#include "gtk_draw.h"
#include "gtk_run.h"

static int gtk_draw_fill(GtkWidget * widget, cairo_t * cr, void * data)
{
  gtk_draw(
    widget,
    cr,
    data,
    fill_draw_void,
    fill_get_index_void,
    fill_get_total_steps_void
  );
  return FALSE;
}

int main(int argc, char * argv[])
{
  int begin, n;
  int * i;
  unsigned int speed;
  double height, width;
  fill * a;
  char title[80] = "Changing colors";
  
  begin = 0;
  i = &begin;
  n = 100;
  
  a = (fill *) alloca(fill_size());
  fill_set(a, i, n, paint_rgb);
  
  width = 500;
  height = 500;
  speed = 100;

  gtk_init(&argc, &argv);
  
  gtk_run(gtk_draw_fill, (fill *) a, width, height, speed, title);

  gtk_main();

  return 0;
}
