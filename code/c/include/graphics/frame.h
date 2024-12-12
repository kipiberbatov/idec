#ifndef _frame_h
#define _frame_h

/* $frame is a rectangular structure for enclosing image data */
typedef struct frame
{
  double left;
  double right;
  double top;
  double bottom;
} frame;

/* $margin specifies cuts from the sides of a rectangle */
typedef struct margin
{
  double left;
  double right;
  double top;
  double bottom;
} margin;

/*
$frame_mesh_data is a structures that contains information about the image
drawn in a frame like frame coordinates, point size and line width
*/
typedef struct frame_mesh_data
{
  double point_size;
  double line_width;
  double * coordinates;
} frame_mesh_data;

void frame_internal_info_for_set_of_points(
  frame_mesh_data * data,
  int n,
  const double * points,
  double width,
  double height,
  const margin * window_margin);

void frame_drawing_region(
  frame * drawing_region,
  double width,
  double height,
  const margin * window_margin);

#endif /* _frame_h */
