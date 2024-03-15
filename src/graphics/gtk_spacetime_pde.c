#include <errno.h>
#include <math.h>
#include <stdlib.h>

#include "double.h"
#include "gtk_spacetime_pde.h"
#include "mesh.h"
#include "rgb.h"

static void point_draw(cairo_t * cr, double x, double y, double r)
{
  cairo_arc(cr, x, y, r, 0, 2 * M_PI);
}

static void unit_square_point_draw_in_window(
  cairo_t * cr, rgb * color, double width, double height,
  double x, double y, double temperature,
  double min_temperature, double max_temperature, int total_colors)
{
  double x_new, y_new;
  double relative_temperature;
  int ind;
  
  x_new = (0.1 + 0.8 * x) * width;
  y_new = (0.1 + 0.8 * y) * height;
  
  relative_temperature = (temperature - min_temperature) / 
                         (max_temperature - min_temperature);
  ind = (int) (relative_temperature * ((double) (total_colors - 1)));
  rgb_color(color, ind, total_colors);
  cairo_set_source_rgb(cr, color->red, color->green, color->blue);
  cairo_set_line_width(cr, 1);
  point_draw(cr, x_new, y_new, (width + height) / 100);
  
  cairo_fill(cr);
  cairo_stroke(cr);
}

struct heat_flow
{
  int * i;
  int n;
  mesh * m;
  double * u;
  double min_temperature;
  double max_temperature;
  int total_colors;
};

int * heat_flow_get_index(heat_flow * a)
{
  return a->i;
}

int heat_flow_total_steps(heat_flow * a)
{
  return a->n;
}

void heat_flow_set(
  heat_flow * a, int * i, int n, mesh * m, double * u, int total_colors)
{
  a->i = i;
  a->n = n;
  a->m = m;
  a->u = u;
  a->total_colors = total_colors;
  a->min_temperature = double_array_min(n * m->cn[0], u);
  a->max_temperature = double_array_max(n * m->cn[0], u);
}

heat_flow *
heat_flow_new(int * i, int n, mesh * m, double * u, int total_colors)
{
  heat_flow * a;
  
  a = malloc(sizeof(heat_flow));
  if (errno)
  {
    fprintf(stderr, 
      "Error during execution of function %s in file %s on line %d: "
      "cannot allocate memory for het flow structure\n",
      __func__, __FILE__,__LINE__);
   return NULL;
  }
  
  heat_flow_set(a, i, n, m, u, total_colors);
  return a;
}

int heat_flow_size(void)
{
  return (int) sizeof(heat_flow);
}

void
gtk_spacetime_pde(cairo_t * cr, double width, double height, heat_flow * a)
{
  int j, m_cn_0, m_dim_embedded;
  double * m_coord, * m_coord_j, * u_i;
  rgb color;
  
  int i = *(a->i);
  int n = a->n;
  mesh * m = a->m;
  double * u = a->u;
  double min_temperature = a->min_temperature;
  double max_temperature = a->max_temperature;
  int total_colors = a->total_colors;
  
  fprintf(stderr, "i = %d\n", i);
  m_cn_0 = m->cn[0];
  m_coord = m->coord;
  m_dim_embedded = m->dim_embedded;
  u_i = u + m_cn_0 * i;

  for (j = 0; j < m_cn_0; ++j)
  {
    m_coord_j = m_coord + m_dim_embedded * j;
    unit_square_point_draw_in_window(
      cr, &color, width, height, m_coord_j[0], m_coord_j[1], u_i[j],
      min_temperature, max_temperature, total_colors);
  }
}
