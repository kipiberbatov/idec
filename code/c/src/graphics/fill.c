#include "fill.h"

struct fill
{
  int i;
  int n;
  painter paint;
};

size_t fill_size(void)
{
  return sizeof(fill);
}

int fill_get_index(const fill * a)
{
  return a->i;
}

int fill_get_index_void(const void * a)
{
  return fill_get_index((const fill *) a);
}

int fill_get_total_steps(const fill * a)
{
  return a->n;
}

int fill_get_total_steps_void(const void * a)
{
  return fill_get_total_steps((const fill *) a);
}

void fill_increment_index(fill * a)
{
  ++a->i;
}

void fill_increment_index_void(void * a)
{
  fill_increment_index((fill *) a);
}

painter fill_get_paint(const fill * a)
{
  return a->paint;
}

void fill_set(fill * a, int i, int n, painter paint)
{
  a->i = i;
  a->n = n;
  a->paint = paint;
}

void fill_draw(
  cairo_t * cr, int * status, double width, double height, const fill * a)
{
  a->paint(cr, status, a->i, a->n);
  cairo_paint(cr);
}

void fill_draw_void(
  cairo_t * cr, int * status, double width, double height, const void * a)
{
  fill_draw(cr, status, width, height, (const fill *) a);
}
