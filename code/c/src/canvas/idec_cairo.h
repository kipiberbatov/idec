#ifndef _idec_cairo_h
#define _idec_cairo_h

#include <cairo.h>

struct idec_graphics_mesh_2d_edge;
struct idec_graphics_mesh_2d_node;

void idec_cairo_paint_white(cairo_t * cr, int * status);

void idec_cairo_set_color_from_scheme_rainbow(
  cairo_t * cr, int * status, int color_index, int total_colors);

void idec_cairo_graphics_mesh_2d_node_draw(
  cairo_t * cr, int * status, const struct idec_graphics_mesh_2d_node * node);

void idec_cairo_graphics_mesh_2d_edge_black_draw(
  cairo_t * cr, int * status, const struct idec_graphics_mesh_2d_edge * edge);

void idec_cairo_graphics_mesh_2d_edge_perpendicular_oriented_draw(
  cairo_t * cr, int * status, const struct idec_graphics_mesh_2d_edge * edge);

#endif /* _idec_cairo_h */
