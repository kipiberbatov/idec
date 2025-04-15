#include <math.h>
#include <stdio.h>

#include "mesh_hemisphere.h"

/* na is the number of meridians, nd is the number of parallels */
void mesh_hemisphere_coordinates(
  double * m_coord, int na, int nd,
  double radius, double x0, double y0, double z0)
{
  int i, j, index;
  double phi, r_cos_theta, r_sin_theta, theta;
  /* theta is the polar angle (elevation),
     phi is the azimuthal (rotation) angle */

  m_coord[0] = x0;
  m_coord[1] = y0;
  m_coord[2] = z0 + radius;
  index = 3;

  for (i = 1; i <= nd; ++i)
  {
    theta = M_PI / 2 - (M_PI / 2 * (double) i) / (double) nd;
    r_cos_theta = radius * cos(theta);
    r_sin_theta = radius * sin(theta);
    for (j = 0; j < na; ++j)
    {
      phi = (2 * M_PI * (double) j) / (double) na;
      m_coord[index + 0] = x0 + r_cos_theta * cos(phi);
      m_coord[index + 1] = y0 + r_cos_theta * sin(phi);
      m_coord[index + 2] = z0 + r_sin_theta;
      index += 3;
    }
  }
}
