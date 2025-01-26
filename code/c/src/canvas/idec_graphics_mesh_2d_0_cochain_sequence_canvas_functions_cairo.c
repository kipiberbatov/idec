#include <math.h>
#include <stdio.h>

#include <cairo.h>

#include "color.h"
#include "idec_animation_canvas_functions.h"
#include "idec_graphics_mesh_2d_0_cochain_sequence.h"
#include "idec_graphics_mesh_2d_node.h"
#include "idec_set_color_from_scheme_rainbow.h"

static void set_background_color_white(void * canvas)
{
  cairo_t * cr = (cairo_t *) canvas;

  cairo_save(cr);
  cairo_set_source_rgb((cairo_t *) canvas, 1, 1, 1);
  cairo_paint(cr);
  cairo_restore(cr);
}

static void idec_graphics_mesh_2d_node_cairo_draw(
  cairo_t * cr,
  int * status,
  const struct idec_graphics_mesh_2d_node * node)
{
  double * coordinates = node->coordinates;

  cairo_save(cr);
  node->set_color(cr, status, node->color_index, node->total_colors);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot set color\n", stderr);
    return;
  }
  cairo_arc(cr, coordinates[0], coordinates[1], node->size, 0, 2 * M_PI);
  cairo_fill(cr);
  cairo_stroke(cr);
  cairo_restore(cr);
}

struct idec_animation_generic_data;

static void draw_snapshot(
  void * canvas,
  int * status,
  const void * data,
  const struct idec_animation_generic_data * generic_data,
  int total_colors,
  void (*set_color_cairo)(void *, int *, int, int))
{
  idec_graphics_mesh_2d_0_cochain_sequence_draw_snapshot(
    (cairo_t *) canvas,
    status,
    (const struct idec_graphics_mesh_2d_0_cochain_sequence *) data,
    generic_data,
    total_colors,
    set_color_cairo,
    (void (*)(void *, int *, const struct idec_graphics_mesh_2d_node *))
      idec_graphics_mesh_2d_node_cairo_draw);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot draw snapshot\n", stderr);
    return;
  }
}

/* This variable will be resolved at runtime by its address */
const struct idec_animation_canvas_functions
idec_graphics_mesh_2d_0_cochain_sequence_canvas_functions_cairo =
{
  set_background_color_white,
  (void (*)(void *, int *, int, int)) idec_set_color_from_scheme_rainbow,
  draw_snapshot
};
