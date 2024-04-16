#include <alloca.h>
#include <stdio.h>
#include <time.h>

#include <gtk/gtk.h>

#include "fill.h"
#include "paint_rgb.h"
#include "gtk_draw.h"
#include "gtk_run.h"

static void write_log(const char * program_name)
{
  time_t rawtime;
  struct tm * p;

  time(&rawtime);
  p = gmtime(&rawtime);

  printf("This file was created after rinning %s\n", program_name);
  printf("Creation time: %02d.%02d.%d %02d:%02d:%02d UTC\n",
    p->tm_mday, p->tm_mon + 1, p->tm_year + 1900,
    p->tm_hour, p->tm_min, p->tm_sec);
}

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
  char title[80] = "Changing colors";
  
  i = 0;
  n = 100;
  
  a = (fill *) alloca(fill_size());
  fill_set(a, i, n, paint_rgb);
  
  width = 500;
  height = 500;
  speed = 100;

  gtk_init(&argc, &argv);
  
  gtk_run(gtk_draw_fill, (fill *) a, width, height, speed, title);

  gtk_main();

  write_log(argv[0]);

  return 0;
}
