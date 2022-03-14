#include "mesh_qc.h"

static double * mesh_qc_cbd_star_p_x(
  const mesh_qc * m, int p, const cs * m_bd_p,
  const double * m_inner_p, const double * m_inner_p_minus_1)
{
  int i, ind, j, j_loc, m_cn_p;
  double sign, m_inner_p_i;
  double * m_bd_p_x, * m_cbd_star_p_x;
  jagged1 hyperfaces;
  jagged2 topology;
  jagged4 * m_cf;

  m_cn_p = m->cn[p];
  m_cf = m->cf;
  m_bd_p_x = m_bd_p->x;
  m_cbd_star_p_x = (double *) malloc(m_bd_p->nzmax * sizeof(double));
  /* NULL pointer check */
  jagged4_part2(&topology, m_cf, p - 1, p - 1);
  ind = 0;
  for (i = 0; i < m_cn_p; ++i)
  {
    jagged2_part1(&hyperfaces, &topology, i);
    m_inner_p_i = m_inner_p[i];
    for (j_loc = 0; j_loc < hyperfaces.a0; ++j_loc)
    {
      sign = m_bd_p_x[ind + j_loc];
      j = hyperfaces.a1[j_loc];
      m_cbd_star_p_x[ind + j_loc] = sign * m_inner_p_i / m_inner_p_minus_1[j];
    }
    ind += hyperfaces.a0;
  }
  return m_cbd_star_p_x;
}

cs * mesh_qc_cbd_star_p(
  const mesh_qc * m, int p, const cs * m_bd_p,
  const double * m_inner_p, const double * m_inner_p_minus_1)
{
  cs * m_cbd_star_p;
  
  m_cbd_star_p = (cs *) malloc(sizeof(cs));
  /* NULL pointer check */
  m_cbd_star_p->nzmax = m_bd_p->nzmax;
  m_cbd_star_p->m = m_bd_p->m;
  m_cbd_star_p->n = m_bd_p->n;
  m_cbd_star_p->p = m_bd_p->p;
  m_cbd_star_p->i = m_bd_p->i;
  m_cbd_star_p->x = 
    mesh_qc_cbd_star_p_x(m, p, m_bd_p, m_inner_p, m_inner_p_minus_1);
  /* NULL pointer check */
  m_cbd_star_p->nz = m_bd_p->nz;
  return m_cbd_star_p;
}

cs ** mesh_qc_cbd_star(const mesh_qc * m, cs ** m_bd, double ** m_inner)
{
  int m_dim, p;
  cs ** m_cbd_star;
  
  m_dim = m->dim;
  m_cbd_star = (cs **) malloc(m_dim * sizeof(cs *));
  /* NULL pointer check */
  for (p = 1; p <= m_dim; ++p)
  {
    m_cbd_star[p - 1] =
      mesh_qc_cbd_star_p(m, p, m_bd[p - 1], m_inner[p], m_inner[p - 1]);
    /* NULL pointer check */
  }
  return m_cbd_star;
}
