#include <errno.h>
#include <string.h>

#include "color.h"
#include "forman.h"
#include "mesh_private.h"
#include "polytope.h"
#include "simplex.h"
#include "quasi_cube.h"

static void forman_coordinates_standard(double * m_forman_coord, const mesh * m)
{
  int i, ind, m_dim_embedded, m_dim, m_cn_p, p;
  int * m_cn;
  double * m_coord;
  jagged1 m_cf_p_0_i;
  jagged2 m_cf_p_0;

  m_dim_embedded = m->dim_embedded;
  m_dim = m->dim;
  m_cn = m->cn;
  m_coord = m->coord;

  memcpy(m_forman_coord, m_coord, sizeof(double) * m_dim_embedded * m_cn[0]);

  ind = m_dim_embedded * m_cn[0];
  for (p = 1; p <= m_dim; ++p)
  {
    mesh_cf_part2(&m_cf_p_0, m, p, 0);
    m_cn_p = m_cn[p];
    for (i = 0; i < m_cn_p; ++i)
    {
      jagged2_part1(&m_cf_p_0_i, &m_cf_p_0, i);
      polytope_coordinates_arithmetic_mean(
        m_forman_coord + ind, m_dim_embedded, &m_cf_p_0_i, m_coord);
      ind += m_dim_embedded;
    }
  }
}

#include <math.h>
static void
forman_coordinates_circular(double * m_forman_coordinates, const mesh * m)
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
    /* segments */
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

/* finds the centroids of a simplicial mesh or of a quasi-cubical mesh */
/* m_forman_coord is set to zero initially */
static void forman_coordinates_centroid(double * m_forman_coord, const mesh * m)
{
  int i, ind, m_dim_embedded, m_dim, m_cn_p, p;
  int * m_cn;
  double * m_coord;
  double s_coord[24]; /* m_dim_embeddded = 3 -> nodes = 8 -> product = 24 */
  simplex s;
  quasi_cube s2;
  jagged1 m_cf_p_0_i;
  jagged2 m_cf_p_0;

  m_dim_embedded = m->dim_embedded;
  m_dim = m->dim;
  m_cn = m->cn;
  m_coord = m->coord;

  s.dim_embedded = m_dim_embedded;
  s2.dim_embedded = m_dim_embedded;
  s.coord = s_coord;
  s2.coord = s_coord;

  memcpy(m_forman_coord, m_coord, sizeof(double) * m_dim_embedded * m_cn[0]);

  ind = m_dim_embedded * m_cn[0];
  for (p = 1; p <= m_dim; ++p)
  {
    s.dim = p;
    s2.dim = p;
    mesh_cf_part2(&m_cf_p_0, m, p, 0);
    m_cn_p = m_cn[p];
    for (i = 0; i < m_cn_p; ++i)
    {
      jagged2_part1(&m_cf_p_0_i, &m_cf_p_0, i);
      mesh_cell_coord(s_coord, &m_cf_p_0_i, m_dim_embedded, m_coord);
      if (m_cf_p_0_i.a0 == p + 1)
        simplex_centroid(m_forman_coord + ind, &s);
      else if (m_cf_p_0_i.a0 == (1 << p))
        quasi_cube_centroid(m_forman_coord + ind, &s2);
      ind += m_dim_embedded;
    }
  }
}

void forman_coordinates(
  double * m_forman_coord, const mesh * m, const char * format)
{
  if (!strcmp(format, "--standard"))
    forman_coordinates_standard(m_forman_coord, m);
  else if (!strcmp(format, "--circular"))
    forman_coordinates_circular(m_forman_coord, m);
  else if (!strcmp(format, "--centroid"))
    forman_coordinates_centroid(m_forman_coord, m);
  else
  {
    errno = EINVAL;
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "format %s is not supported\n", format);
  }
}
