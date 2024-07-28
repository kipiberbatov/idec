#include "image.h"

/* this is only for the unit square */
void image_new_coordinates(
  double * new,
  const mesh * m,
  double width,
  double height)
{
  int i;
  int n = m->cn[0];
  double * x = m->coord;

  for (i = 0; i < n; ++i)
  {
    new[2 * i] = (0.1 + 0.8 * x[2 * i]) * width;
    new[2 * i + 1] = (0.1 + 0.8 * x[2 * i + 1]) * height;
  }
}

double image_point_size(double width, double height)
{
  return (width + height) / 100;
}
