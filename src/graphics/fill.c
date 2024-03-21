#include <stdio.h>
#include "fill.h"
#include "painter.h"

struct fill
{
  int * i;
  int n;
  int total_colors;
  painter paint;
};

int fill_size(void)
{
  return sizeof(fill);
}

int * fill_get_index(fill * a)
{
  return a->i;
}

int * fill_get_index_void(void * a)
{
  return fill_get_index((fill *) a);
}

int fill_get_total_steps(const fill * a)
{
  return a->n;
}

int fill_get_total_steps_void(const void * a)
{
  return fill_get_total_steps((const fill *) a);
}

int fill_get_total_colors(const fill * a)
{
  return a->total_colors;
}

painter fill_get_paint(fill * a)
{
  return a->paint;
}

void fill_set(fill * a, int * i, int n, int total_colors, painter paint)
{
  a->i = i;
  a->n = n;
  a->total_colors = total_colors;
  a->paint = paint;
}

void fill_draw(cairo_t * cr, double width, double height, fill * a)
{
  a->paint(cr, *(a->i), a->n);
  cairo_paint(cr);
}

void fill_draw_void(cairo_t * cr, double width, double height, void * a)
{
  fill_draw(cr, width, height, (fill *) a);
}
