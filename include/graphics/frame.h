#ifndef _frame_h
#define _frame_h

/* $frame is a rectangular structure for enclosing image data */
typedef struct frame frame;

/* $margin specifies cuts from the sides of a rectangle */
typedef struct margin margin;

/*
$frame_mesh_data is a structures that contains information about the image
drawn in a frame like frame coordinates, point size and line width
*/
typedef struct frame_mesh_data frame_mesh_data;

/*
From the input data wind the window frame and the necessary data.
*/
void frame_internal_info_for_set_of_points(
  frame * window_frame,
  frame_mesh_data * data,
  int n,
  const double * points,
  double width,
  double height,
  const margin * window_margin);

/* implementation */

struct frame {double left, right, top, bottom;};
struct margin {double left, right, top, bottom;};
struct frame_mesh_data {double point_size, line_width, * coordinates;};

#endif /* _frame_h */
