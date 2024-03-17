#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <cairo.h>

#include "double.h"
#include "diffusion.h"

struct diffusion
{
  int * i;
  int n;
  mesh * m;
  double * new_coordinates;
  double point_size;
  double * u;
  double min_value;
  double max_value;
  int total_colors;
  painter_t painter;
};

int diffusion_size(void)
{
  return (int) sizeof(diffusion);
}

int * diffusion_get_index(diffusion * a)
{
  return a->i;
}

int diffusion_total_steps(const diffusion * a)
{
  return a->n;
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

painter_t diffusion_get_painter(diffusion * a)
{
  return a->painter;
}

void diffusion_set(
  diffusion * a,
  int * i,
  int n,
  mesh * m,
  double * new_coordinates,
  double point_size,
  double * u,
  int total_colors,
  painter_t painter)
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
  a->painter = painter;
}

typedef struct colored_2d_point colored_2d_point;

struct colored_2d_point
{
  int total_colors;
  double x;
  double y;
  double point_size;
  double relative_value;
  painter_t painter;
};

void colored_2d_point_draw(cairo_t * cr, colored_2d_point * p)
{
  int ind;
  
  ind = (int) (p->relative_value * ((double) (p->total_colors - 1)));
  p->painter(cr, ind, p->total_colors);
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
  painter_t painter;
};

void colored_2d_zero_cochain_cairo_draw(
  cairo_t * cr,
  const colored_2d_zero_cochain * c)
{
  int c_size, j;
  double c_max, c_min, denominator;
  double * c_coordinates, * c_values, * x_j;
  // painter_t painter;
  colored_2d_point p;
  
  c_min = c->min_value;
  c_max = c->max_value;
  c_size = c->size;
  c_coordinates = c->coordinates;
  c_values = c->values;
  p.point_size = c->point_size;
  p.total_colors = c->total_colors;
  p.painter = c->painter;
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

void diffusion_draw_snapshot(
  cairo_t * cr,
  double width,
  double height,
  diffusion * a)
{
  int j, m_cn_0, m_dim_embedded;
  int * i;
  double * m_coord, * m_coord_j, * u, * u_i;
  mesh * m;
  colored_2d_zero_cochain c;
  
  i = diffusion_get_index(a);
  m = diffusion_get_mesh(a);
  u = diffusion_get_values(a);
  
  c.size = m->cn[0];
  c.total_colors = diffusion_get_total_colors(a);
  c.coordinates = diffusion_get_new_coordinates(a);
  c.values = u + m->cn[0] * (*i);
  c.point_size = diffusion_get_point_size(a);
  c.min_value = diffusion_min_value(a);
  c.max_value = diffusion_max_value(a);
  c.painter = diffusion_get_painter(a);
  colored_2d_zero_cochain_cairo_draw(cr, &c);
}
