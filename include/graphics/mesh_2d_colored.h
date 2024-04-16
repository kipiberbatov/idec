#ifndef _mesh_2d_colored_h
#define _mesh_2d_colored_h

#include <cairo.h>

#include "mesh.h"
#include "painter.h"

/********************************** 0-cells ***********************************/

typedef struct mesh_2d_colored_node mesh_2d_colored_node;

void mesh_2d_colored_node_cairo_draw(
  cairo_t * cr,
  mesh_2d_colored_node * node);

typedef struct mesh_2d_colored_zero_cochain mesh_2d_colored_zero_cochain;

void mesh_2d_colored_zero_cochain_cairo_draw(
  cairo_t * cr,
  const mesh_2d_colored_zero_cochain * c);

typedef struct mesh_2d_colored_zero_cochain_sequence
mesh_2d_colored_zero_cochain_sequence;

struct mesh_2d_colored_zero_cochain_sequence
{
  int index;
  int total_steps;
  mesh * m;
  double * values;
  
  int total_colors;
  double * new_coordinates;
  double point_size;
  double min_value;
  double max_value;
  painter paint;
};

int mesh_2d_colored_zero_cochain_sequence_get_index_void(const void * a);
int mesh_2d_colored_zero_cochain_sequence_get_total_steps_void(const void * a);
void mesh_2d_colored_zero_cochain_sequence_increment_index_void(void * a);

void mesh_2d_colored_zero_cochain_sequence_snapshot_cairo_draw(
  cairo_t * cr,
  double width,
  double height,
  mesh_2d_colored_zero_cochain_sequence * a);

void mesh_2d_colored_zero_cochain_sequence_snapshot_cairo_draw_void(
  cairo_t * cr,
  double width,
  double height,
  void * a);

/********************************** 1-cells ***********************************/

typedef struct mesh_2d_colored_edge mesh_2d_colored_edge;

void mesh_2d_colored_edge_cairo_draw(
  cairo_t * cr,
  mesh_2d_colored_edge * edge);

typedef struct mesh_2d_colored_one_cochain mesh_2d_colored_one_cochain;

void mesh_2d_colored_one_cochain_cairo_draw(
  cairo_t * cr,
  const mesh_2d_colored_one_cochain * c);

typedef struct mesh_2d_colored_one_cochain_sequence
mesh_2d_colored_one_cochain_sequence;

struct mesh_2d_colored_one_cochain_sequence
{
  int index;
  int total_steps;
  mesh * m;
  double * values;
  
  int total_colors;
  double * new_coordinates;
  double line_width;
  double min_value;
  double max_value;
  painter paint;
};

int mesh_2d_colored_one_cochain_sequence_get_index_void(const void * a);
int mesh_2d_colored_one_cochain_sequence_get_total_steps_void(const void * a);
void mesh_2d_colored_one_cochain_sequence_increment_index_void(void * a);

void mesh_2d_colored_one_cochain_sequence_snapshot_cairo_draw(
  cairo_t * cr,
  double width,
  double height,
  mesh_2d_colored_one_cochain_sequence * a);

void mesh_2d_colored_one_cochain_sequence_snapshot_cairo_draw_void(
  cairo_t * cr,
  double width,
  double height,
  void * a);

#endif /* _mesh_2d_colored_h */
