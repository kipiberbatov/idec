#ifndef _idec_cairo_h
#define _idec_cairo_h

#include <cairo.h>

struct arc_2d;
struct idec_graphics_mesh_2d_edge;
struct idec_graphics_mesh_2d_node;
struct idec_graphics_rectangle;
struct idec_rgb;
struct line_2d;

void idec_cairo_paint_white(cairo_t * cr, int * status);

void
idec_cairo_paint_rgb(cairo_t * cr, int * status, const struct idec_rgb * color);

void idec_cairo_graphics_2d_line_draw(
  cairo_t * cr, int * status, const struct line_2d * line);

void idec_cairo_graphics_2d_arc_draw(
  cairo_t * cr, int * status, const struct arc_2d * arc);

void idec_cairo_graphics_rectangle_draw(
  cairo_t * cr, int * status, const struct idec_graphics_rectangle * rectangle,
  void (*get_color)(struct idec_rgb *, const void *));

void idec_cairo_graphics_mesh_2d_node_draw(
  cairo_t * cr, int * status, const struct idec_graphics_mesh_2d_node * node,
  void (*get_color)(struct idec_rgb *, const void *));

void idec_cairo_graphics_mesh_2d_edge_black_draw(
  cairo_t * cr, int * status, const struct idec_graphics_mesh_2d_edge * edge,
  void (*draw_curve)(cairo_t *, int *, const void *));

void idec_cairo_graphics_mesh_2d_edge_oriented_draw(
  cairo_t * cr, int * status, const struct idec_graphics_mesh_2d_edge * edge,
  void (*get_color)(struct idec_rgb *, const void *));

#endif /* _idec_cairo_h */
