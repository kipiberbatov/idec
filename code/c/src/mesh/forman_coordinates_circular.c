#include <math.h>
#include <string.h>

#include "forman_coordinates_private.h"

/* Calculate the centroids of the Forman subdivision of mesh_circular() */
void forman_coordinates_circular(double * m_forman_coordinates, const mesh * m)
{
  int i, index, j, na, nd, product;
  int * m_cf_a3_2_0, * m_cn;
  double r, r0, t, theta, u, x0, y0;
  double * m_coordinates;

  m_cn = m->cn;
  m_cf_a3_2_0 = m->cf->a3 + m_cn[1];
  m_coordinates = m->coord;

  memcpy(m_forman_coordinates, m_coordinates, sizeof(double) * 2 * m_cn[0]);

  product = m_cn[2];
  /* calculate na */
  na = 0;
  i = 0;
  while (m_cf_a3_2_0[i] == 3)
  {
    ++na;
    ++i;
  }
  nd = product / na;
  /* new coordinates corresponding to old edges */
  index = 2 * m_cn[0];
  x0 = m_coordinates[0];
  y0 = m_coordinates[1];
  {
    double rx = m_coordinates[2 * m_cn[0] - 2];
    double ry = m_coordinates[2 * m_cn[0] - 1];
    r = sqrt(rx * rx + ry * ry);
  }
  r0 = r / nd;
  theta = M_PI * 2 / na;
  for (i = 0; i < nd; ++i)
  {
    /* rays */
    u = r0 * (double) (2 * i + 1) / 2.;
    for (j = 0; j < na; ++j)
    {
      t = theta * (double) j;
      m_forman_coordinates[index] = u * cos(t) + x0;
      m_forman_coordinates[index + 1] = u * sin(t) + y0;
      index += 2;
    }
    /* arcs */
    u = r0 * (double) (i + 1);
    for (j = 0; j < na; ++j)
    {
      t = theta * (double) (2 * j + 1) / 2.;
      m_forman_coordinates[index] = u * cos(t) + x0;
      m_forman_coordinates[index + 1] = u * sin(t) + y0;
      index += 2;
    }
  }
  /* new coordinates corresponding to old faces */
  for (i = 0; i < nd; ++i)
  {
    u = r0 * (2 * i + 1) / 2.;
    for (j = 0; j < na; ++j)
    {
      t = theta * (double) (2 * j + 1) / 2.;
      m_forman_coordinates[index] = u * cos(t) + x0;
      m_forman_coordinates[index + 1] = u * sin(t) + y0;
      index += 2;
    }
  }
}
