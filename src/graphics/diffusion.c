#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <cairo.h>

#include "double.h"
#include "diffusion.h"
#include "painter.h"

struct diffusion
{
  int i;
  int n;
  mesh * m;
  double * new_coordinates;
  double point_size;
  double * u;
  double min_value;
  double max_value;
  int total_colors;
  painter paint;
};

int diffusion_size(void)
{
  return (int) sizeof(diffusion);
}

int diffusion_get_index(const diffusion * a)
{
  return a->i;
}

int diffusion_get_index_void(const void * a)
{
  return diffusion_get_index((const diffusion *) a);
}

int diffusion_get_total_steps(const diffusion * a)
{
  return a->n;
}

int diffusion_get_total_steps_void(const void * a)
{
  return diffusion_get_total_steps((const diffusion *) a);
}

void diffusion_increment_index(diffusion * a)
{
  ++a->i;
}

void diffusion_increment_index_void(void * a)
{
  diffusion_increment_index((diffusion *) a);
}

mesh * diffusion_get_mesh(diffusion * a)
{
  return a->m;
}

double * diffusion_get_new_coordinates(diffusion * a)
{
  return a->new_coordinates;
}

double diffusion_get_point_size(const diffusion * a)
{
  return a->point_size;
}

double * diffusion_get_values(diffusion * a)
{
  return a->u;
}

double diffusion_min_value(const diffusion * a)
{
  return a->min_value;
}

double diffusion_max_value(const diffusion * a)
{
  return a->max_value;
}

int diffusion_get_total_colors(const diffusion * a)
{
  return a->total_colors;
}

painter diffusion_get_paint(diffusion * a)
{
  return a->paint;
}

void diffusion_set(
  diffusion * a,
  int i,
  int n,
  mesh * m,
  double * new_coordinates,
  double point_size,
  double * u,
  int total_colors,
  painter paint)
{
  a->i = i;
  a->n = n;
  a->m = m;
  a->new_coordinates = new_coordinates;
  a->point_size = point_size;
  a->u = u;
  a->total_colors = total_colors;
  a->min_value = double_array_min(n * m->cn[0], u);
  a->max_value = double_array_max(n * m->cn[0], u);
  a->paint = paint;
}

typedef struct colored_2d_point colored_2d_point;

struct colored_2d_point
{
  int total_colors;
  double x;
  double y;
  double point_size;
  double relative_value;
  painter paint;
};

void colored_2d_point_draw(cairo_t * cr, colored_2d_point * p)
{
  int ind;
  
  ind = (int) (p->relative_value * ((double) (p->total_colors - 1)));
  p->paint(cr, ind, p->total_colors);
  cairo_set_line_width(cr, 1);
  cairo_arc(cr, p->x, p->y, p->point_size, 0, 2 * M_PI);
  
  cairo_fill(cr);
  cairo_stroke(cr);
}

typedef struct colored_2d_zero_cochain colored_2d_zero_cochain;

struct colored_2d_zero_cochain
{
  int size;
  int total_colors;
  double * coordinates;
  double * values;
  double point_size;
  double min_value;
  double max_value;
  painter paint;
};

void colored_2d_zero_cochain_cairo_draw(
  cairo_t * cr,
  const colored_2d_zero_cochain * c)
{
  int c_size, j;
  double c_max, c_min, denominator;
  double * c_coordinates, * c_values, * x_j;
  colored_2d_point p;
  
  c_min = c->min_value;
  c_max = c->max_value;
  c_size = c->size;
  c_coordinates = c->coordinates;
  c_values = c->values;
  p.point_size = c->point_size;
  p.total_colors = c->total_colors;
  p.paint = c->paint;
  denominator = c_max - c_min;
  for (j = 0; j < c_size; ++j)
  {
    x_j = c_coordinates + 2 * j;
    p.x = x_j[0];
    p.y = x_j[1];
    p.relative_value = (c_values[j] - c_min) / denominator;
    colored_2d_point_draw(cr, &p);
  }
}

void diffusion_draw(cairo_t * cr, double width, double height, diffusion * a)
{
  int i;
  double * u;
  mesh * m;
  colored_2d_zero_cochain c;
  
  i = diffusion_get_index(a);
  m = diffusion_get_mesh(a);
  u = diffusion_get_values(a);
  
  c.size = m->cn[0];
  c.total_colors = diffusion_get_total_colors(a);
  c.coordinates = diffusion_get_new_coordinates(a);
  c.values = u + m->cn[0] * i;
  c.point_size = diffusion_get_point_size(a);
  c.min_value = diffusion_min_value(a);
  c.max_value = diffusion_max_value(a);
  c.paint = diffusion_get_paint(a);
  colored_2d_zero_cochain_cairo_draw(cr, &c);
}

void diffusion_draw_void(cairo_t * cr, double width, double height, void * a)
{
  diffusion_draw(cr, width, height, (diffusion *) a);
}
