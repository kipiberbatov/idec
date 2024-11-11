#include <math.h>

#include "mesh_2d_colored_edge.h"
#include "mesh_2d_colored_one_cochain.h"

#define max(a, b) (a) > (b) ? a : b

void mesh_2d_colored_one_cochain_cairo_draw(
  cairo_t * cr,
  const mesh_2d_colored_one_cochain * c)
{
  int c_number_of_edges, i, ind;
  int * cf_1_0_a1, * cf_1_0_i;
  double c_max, c_min, denominator, v0, v1, v_norm, z0, z1;
  double * bd_1, * c_coordinates, * c_values, * e0, * e1;
  jagged2 * cf_1_0;
  mesh_2d_colored_edge edge;

  c_min = c->min_value;
  c_max = c->max_value;
  c_coordinates = c->coordinates;
  c_values = c->values;
  edge.point_size = c->point_size / 4;
  edge.width = c->line_width / 4;
  edge.total_colors = c->total_colors;
  edge.paint = c->paint;
  denominator = c_max - c_min;
  cf_1_0 = c->cf_1_0;
  bd_1 = c->bd_1;
  c_number_of_edges = cf_1_0->a0;
  cf_1_0_i = cf_1_0->a2;
  cf_1_0_a1 = cf_1_0->a1;
  for (i = 0; i < c_number_of_edges; ++i)
  {
    e0 = c_coordinates + 2 * cf_1_0_i[0];
    e1 = c_coordinates + 2 * cf_1_0_i[1];
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, edge.width);
    cairo_move_to(cr, e0[0], e0[1]);
    cairo_line_to(cr, e1[0], e1[1]);
    cairo_stroke(cr);
    if (!(c->is_mesh_edge_skeleton))
    {
      v0 = e1[1] - e0[1];
      v1 = e0[0] - e1[0];
      v_norm = sqrt(v0 * v0 + v1 * v1);
      v0 = (v0 / v_norm) * edge.point_size;
      v1 = (v1 / v_norm) * edge.point_size;
      z0 = (e0[0] + e1[0]) / 2;
      z1 = (e0[1] + e1[1]) / 2;
      if (bd_1[2 * i] * c_values[i] < 0)
      {
        edge.coordinates_0[0] = z0 - v0;
        edge.coordinates_0[1] = z1 - v1;
        edge.coordinates_1[0] = z0 + v0;
        edge.coordinates_1[1] = z1 + v1;
      }
      else
      {
        edge.coordinates_0[0] = z0 + v0;
        edge.coordinates_0[1] = z1 + v1;
        edge.coordinates_1[0] = z0 - v0;
        edge.coordinates_1[1] = z1 - v1;
      }
      if (denominator == 0.)
        edge.relative_value = 0.;
      else
        edge.relative_value = (fabs(c_values[i]) - c_min) / denominator;
      ind = (int) (edge.relative_value * ((double) (edge.total_colors - 1)));
      edge.paint(cr, ind, edge.total_colors);
      cairo_set_line_width(cr, edge.width);
      cairo_move_to(cr, edge.coordinates_0[0], edge.coordinates_0[1]);
      cairo_line_to(cr, edge.coordinates_1[0], edge.coordinates_1[1]);
      cairo_arc(cr, edge.coordinates_1[0], edge.coordinates_1[1],
        edge.point_size / 4, 0, 2 * M_PI);
      cairo_stroke(cr);
    }
    cf_1_0_i += cf_1_0_a1[i];
  }
}
