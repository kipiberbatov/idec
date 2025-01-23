#include <errno.h>
#include <math.h>
#include <stdlib.h>

#include "double.h"
#include "diffusion.h"
#include "gtk_spacetime_pde.h"
#include "mesh.h"
#include "rgb.h"

static void unit_square_point_draw_in_window(
  cairo_t * cr, rgb * color, int * status, double width, double height,
  double x, double y, double value,
  double min_value, double max_value, int total_colors)
{
  double x_new, y_new;
  double relative_value;
  int ind;

  x_new = (0.1 + 0.8 * x) * width;
  y_new = (0.1 + 0.8 * y) * height;

  relative_value = (value - min_value) /
                         (max_value - min_value);
  ind = (int) (relative_value * ((double) (total_colors - 1)));
  rgb_color(color, status, ind, total_colors);
  cairo_set_source_rgb(cr, color->red, color->green, color->blue);
  cairo_set_line_width(cr, 1);
  cairo_arc(cr, x_new, y_new, (width + height) / 100, 0, 2 * M_PI);

  cairo_fill(cr);
  cairo_stroke(cr);
}

void gtk_spacetime_pde(
  cairo_t * cr, int * status, double width, double height, diffusion * a)
{
  int i, j, m_cn_0, m_dim_embedded, total_colors;
  double min_value, max_value;
  double * m_coord, * m_coord_j, * u, * u_i;
  rgb color;
  mesh * m;

  i = diffusion_get_index(a);
  m = diffusion_get_mesh(a);
  u = diffusion_get_values(a);
  min_value = diffusion_min_value(a);
  max_value = diffusion_max_value(a);
  total_colors = diffusion_get_total_colors(a);

  m_cn_0 = m->cn[0];
  m_coord = m->coord;
  m_dim_embedded = m->dim_embedded;
  u_i = u + m_cn_0 * i;

  for (j = 0; j < m_cn_0; ++j)
  {
    m_coord_j = m_coord + m_dim_embedded * j;
    unit_square_point_draw_in_window(
      cr, &color, status, width, height, m_coord_j[0], m_coord_j[1], u_i[j],
      min_value, max_value, total_colors);
  }
}
