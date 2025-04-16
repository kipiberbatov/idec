#include <math.h>
#include <string.h>

#include "forman_coordinates_private.h"

/* Calculate the centroids of the Forman subdivision of mesh_circular() */
void forman_coordinates_circular(double * m_forman_coordinates, const mesh * m)
{
  int i, index, j, na, nd, m_dim_embedded, product;
  int * m_cf_a3_2_0, * m_cn;
  double r, rx, ry, t, theta, x0, y0;
  double * m_coordinates, * node0, * node1;

  m_cn = m->cn;
  m_cf_a3_2_0 = m->cf->a3 + m_cn[1];
  m_coordinates = m->coord;
  m_dim_embedded = m->dim_embedded;
  x0 = m_coordinates[0];
  y0 = m_coordinates[1];

  /* calculate na and nd */
  product = m_cn[2];
  na = 0;
  i = 0;
  while (m_cf_a3_2_0[i] == 3)
  {
    ++na;
    ++i;
  }
  nd = product / na;

  /* elementary angle */
  theta = M_PI * 2 / na;

  /* new coordinates corresponding to old nodes */
  memcpy(m_forman_coordinates, m_coordinates,
         sizeof(double) * m_dim_embedded * m_cn[0]);
  index = m_dim_embedded * m_cn[0];

  /* new coordinates corresponding to old edges */
  for (i = 0; i < nd; ++i)
  {
    node0 = m_coordinates + m_dim_embedded * (1 + na * (i - 1));
    node1 = m_coordinates + m_dim_embedded * (1 + na * i);
    /* rays */
    if (i == 0)
    {
      rx = (node1[0] - x0) / 2;
      ry = (node1[1] - y0) / 2;
      r = sqrt(rx * rx + ry * ry);
    }
    else
    {
      rx = (node0[0] + node1[0]) / 2 - x0;
      ry = (node0[1] + node1[1]) / 2 - y0;
      r = sqrt(rx * rx + ry * ry);
    }
    for (j = 0; j < na; ++j)
    {
      t = theta * (double) j;
      m_forman_coordinates[index + 0] = x0 + r * cos(t);
      m_forman_coordinates[index + 1] = y0 + r * sin(t);
      memset(m_forman_coordinates + index + 2, 0,
             sizeof(double) * (m_dim_embedded - 2));
      index += m_dim_embedded;
    }
    /* arcs */
    rx = node1[0] - x0;
    ry = node1[1] - y0;
    r = sqrt(rx * rx + ry * ry);
    for (j = 0; j < na; ++j)
    {
      t = theta * (double) (2 * j + 1) / 2.;
      m_forman_coordinates[index + 0] = x0 + r * cos(t);
      m_forman_coordinates[index + 1] = y0 + r * sin(t);
      memset(m_forman_coordinates + index + 2, 0,
             sizeof(double) * (m_dim_embedded - 2));
      index += m_dim_embedded;
    }
  }

  /* new coordinates corresponding to old faces */
  for (i = 0; i < nd; ++i)
  {
    node0 = m_coordinates + m_dim_embedded * (1 + na * (i - 1));
    node1 = m_coordinates + m_dim_embedded * (1 + na * i);
    /* rays */
    if (i == 0)
    {
      rx = (node1[0] - x0) / 2;
      ry = (node1[1] - y0) / 2;
      r = sqrt(rx * rx + ry * ry);
    }
    else
    {
      rx = (node0[0] + node1[0]) / 2 - x0;
      ry = (node0[1] + node1[1]) / 2 - y0;
      r = sqrt(rx * rx + ry * ry);
    }
    r = sqrt(rx * rx + ry * ry);
    for (j = 0; j < na; ++j)
    {
      t = theta * (double) (2 * j + 1) / 2.;
      m_forman_coordinates[index + 0] = x0 + r * cos(t);
      m_forman_coordinates[index + 1] = y0 + r * sin(t);
      memset(m_forman_coordinates + index + 2, 0,
             sizeof(double) * (m_dim_embedded - 2));
      index += m_dim_embedded;
    }
  }
}
