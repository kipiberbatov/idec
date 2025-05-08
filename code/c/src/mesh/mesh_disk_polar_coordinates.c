#include <math.h>

#include "mesh_disk_polar.h"

void mesh_disk_polar_coordinates(
  double * m_coord, int na, int nd, double radius, double x0, double y0)
{
  int i, j, offset;
  double cost, length, sint, t;

  m_coord[0] = x0;
  m_coord[1] = y0;

  for (j = 0; j < na; ++j)
  {
    t = (2 * M_PI * (double) j) / (double) na;
    cost = cos(t);
    sint = sin(t);
    for (i = 0; i < nd; ++i)
    {
      offset = 2 * (1 + na * i + j);
      length = radius * (double) (i + 1) / (double) nd;
      m_coord[offset] = x0 + length * cost;
      m_coord[offset + 1] = y0 + length * sint;
    }
  }
}
