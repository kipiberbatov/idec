#include <errno.h>
#include <stdlib.h>
#include "double.h"
#include "mesh_private.h"
#include "mesh_qc.h"

static double mesh_qc_vol_p_i(const jagged2 * m_cf_p_0, int m_dim_embedded,
                              double * m_coord, int p, int i)
{
  double s_coord[24]; /* m_dim_embeddded = 3 -> nodes = 8 -> product = 24 */
  quasi_cube s;
  jagged1 m_cf_p_0_i;

  s.dim_embedded = m_dim_embedded;
  s.dim = p;
  jagged2_part1(&m_cf_p_0_i, m_cf_p_0, i);
  mesh_cell_coord(s_coord, &m_cf_p_0_i, m_dim_embedded, m_coord);
  s.coord = s_coord;
  return quasi_cube_measure(&s);
}

static void mesh_qc_vol_nonzero(double * m_vol_p, const mesh_qc * m, int p)
{
  int i, m_cn_p;
  jagged2 m_cf_p_0;

  m_cn_p = m->cn[p];
  mesh_cf_part2(&m_cf_p_0, m, p, 0);
  for (i = 0; i < m_cn_p; ++i)
    m_vol_p[i] = mesh_qc_vol_p_i(&m_cf_p_0, m->dim_embedded, m->coord, p, i);
}

double * mesh_qc_vol_p(const mesh_qc * m, int p)
{
  double * m_vol_p;

  m_vol_p = (double *) malloc(sizeof(double) * m->cn[p]);
  if (errno)
  {
    fprintf(stderr,
            "mesh_qc_vol_p - cannot allocate memory for m_vol[%d]\n", p);
    return NULL;
  }

  if (p == 0)
    double_array_assign_constant(m_vol_p, m->cn[p], 1.);
  else
    mesh_qc_vol_nonzero(m_vol_p, m, p);

  return m_vol_p;
}

double ** mesh_qc_vol(const mesh_qc * m)
{
  int m_dim, p;
  double ** m_vol;

  m_dim = m->dim;

  m_vol = (double **) malloc(sizeof(double *) * (m_dim + 1));
  if (errno)
  {
    fputs("mesh_qc_vol - cannot allocate memory for m_vol\n", stderr);
    return NULL;
  }

  for(p = 0; p <= m_dim; ++p)
  {
    m_vol[p] = mesh_qc_vol_p(m, p);
    if (errno)
    {
      fprintf(stderr, "mesh_qc_vol - cannot calculate m_vol[%d]\n", p);
      double_array2_free(m_vol, p);
      return NULL;
    }
  }

  return m_vol;
}
