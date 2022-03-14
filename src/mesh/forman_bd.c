#include <stdlib.h>
#include <stdio.h>
#include "forman_private.h"
#include "list.h"

static double * forman_bd_x(
  const mesh * m_forman, cs ** m_bd, int m_forman_bd_p_f_nzmax,
  const jagged3 * m_forman_cbi, int p_f)
{
  int i, i_f, ind, j, j_f, j_f_loc, k, l, p, q, r, s;
  int * m_forman_cn;
  double sign, sign_loc;
  double * m_forman_bd_p_f_x;
  jagged1 m_forman_cbi_p_f_i_f, m_forman_cbi_p_f_minus_1_j_f,
          m_forman_hyperface;
  jagged2 m_forman_cbi_p_f, m_forman_cbi_p_f_minus_1, m_forman_hyperfaces;
  jagged4 * m_forman_cf;
  
  m_forman_cn = m_forman->cn;
  m_forman_cf = m_forman->cf;
  jagged3_part1(&m_forman_cbi_p_f, m_forman_cbi, p_f);
  jagged3_part1(&m_forman_cbi_p_f_minus_1, m_forman_cbi, p_f - 1);
  jagged4_part2(&m_forman_hyperfaces, m_forman_cf, p_f - 1, p_f - 1);
  
  m_forman_bd_p_f_x = (double *) malloc(m_forman_bd_p_f_nzmax * sizeof(double));
  /* NULL pointer check */
  ind = 0;
  for (i_f = 0; i_f < m_forman_cn[p_f]; ++i_f)
  {
    jagged2_part1(&m_forman_cbi_p_f_i_f, &m_forman_cbi_p_f, i_f);
    list_get_4_values(m_forman_cbi_p_f_i_f.a1, &r, &k, &s, &l);
    jagged2_part1(&m_forman_hyperface, &m_forman_hyperfaces, i_f);
    for (j_f_loc = 0; j_f_loc < m_forman_hyperface.a0; ++j_f_loc)
    {
      j_f = jagged1_part1(&m_forman_hyperface, j_f_loc);
      jagged2_part1(&m_forman_cbi_p_f_minus_1_j_f,
                    &m_forman_cbi_p_f_minus_1, j_f);
      list_get_4_values(m_forman_cbi_p_f_minus_1_j_f.a1, &p, &i, &q, &j);
      if (r == p)
      {
        sign_loc = p_f % 2 == 0 ? 1. : -1.;
        sign = sign_loc * cs_part(m_bd[q - 1], l, j);
      }
      else
        sign = cs_part(m_bd[p], i, k);
      m_forman_bd_p_f_x[ind + j_f_loc] = sign;
    }
    ind += m_forman_hyperface.a0;
  }
  return m_forman_bd_p_f_x;
}

cs * forman_bd_p_f(
  const mesh * m_forman, cs ** m_bd, const jagged3 * m_forman_cbi, int p_f)
{
  int * m_forman_cn;
  cs * m_forman_bd_p_f;
  
  m_forman_cn = m_forman->cn;
  m_forman_bd_p_f = (cs *) malloc(sizeof(cs));
  /* NULL pointer check */
  m_forman_bd_p_f->nzmax = mesh_bd_nzmax(m_forman, p_f);
  m_forman_bd_p_f->m = m_forman_cn[p_f - 1];
  m_forman_bd_p_f->n = m_forman_cn[p_f];
  m_forman_bd_p_f->p = mesh_bd_p(m_forman, p_f);
  /* NULL pointer check */
  m_forman_bd_p_f->i = mesh_bd_i(m_forman, p_f);
  /* NULL pointer check */
  m_forman_bd_p_f->x = forman_bd_x(m_forman, m_bd, m_forman_bd_p_f->nzmax,
                                   m_forman_cbi, p_f);
  /* NULL pointer check */
  m_forman_bd_p_f->nz = -1;
  return m_forman_bd_p_f;
}

cs ** forman_bd(const mesh * m, const mesh * m_forman, cs ** m_bd)
{
  int m_dim, p_f;
  int * m_forman_cn;
  cs ** m_forman_bd;
  jagged3 * m_forman_cbi;

  m_dim = m->dim;
  m_forman_cn = m_forman->cn;
  m_forman_cbi = forman_cbi(m, m_forman_cn);
  /* NULL pointer check */
  m_forman_bd = (cs **) malloc(m_dim * sizeof(cs *));
  /* NULL pointer check */
  for (p_f = 1; p_f <= m_dim; ++p_f)
  {
    m_forman_bd[p_f - 1] = forman_bd_p_f(m_forman, m_bd, m_forman_cbi, p_f);
    /* NULL pointer check */
  }
  jagged3_free(m_forman_cbi);
  return m_forman_bd;
}
