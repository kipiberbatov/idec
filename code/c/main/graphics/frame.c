#include <stdio.h>

#include "frame.h"

int main(int argc, char ** argv)
{
  int i;
  int n = 4;
  const double points[8] = {-2, 0,  0, -1,  2, 0,  0, 1};
  double data_coordinates[8];
  double width = 300;
  double height = 400;
  margin window_margin = {5, 10, 20, 10};
  frame window_frame;
  frame_mesh_data data;

  frame_drawing_region(&window_frame, width, height, &window_margin);
  printf("window_frame = (%g, %g) * (%g, %g)\n",
    window_frame.left, window_frame.right,
    window_frame.top, window_frame.bottom);

  data.coordinates = data_coordinates;
  frame_internal_info_for_set_of_points(
    &data,
    n,
    points,
    width,
    height,
    &window_margin);

  printf("point_size = %g\n", data.point_size);
  printf("line_width = %g\n", data.line_width);
  for (i = 0; i < 4; ++i)
    printf("(x[%d], y[%d]) = (%g, %g)\n",
      i, i, data_coordinates[2 * i], data_coordinates[2 * i + 1]);
  return 0;
}
