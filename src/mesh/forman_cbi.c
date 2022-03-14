#include <stdlib.h>
#include "forman_private.h"
#include "list.h"

static int * forman_cbi_a1(int m_dim, const int * m_forman_cn)
{
  int q_f;
  int * m_forman_cbi_a1;
  
  m_forman_cbi_a1 = (int *) malloc((m_dim + 1) * sizeof(int));
  /* NULL pointer check */
  for (q_f = 0; q_f <= m_dim; ++q_f)
    m_forman_cbi_a1[q_f] = m_forman_cn[q_f];
  return m_forman_cbi_a1;
}

static int * forman_cbi_a2(int m_forman_cbi_a2_size)
{
  int ind = 0;
  int * m_forman_cbi_a2;
  
  m_forman_cbi_a2 = (int *) malloc(m_forman_cbi_a2_size * sizeof(int));
  /* NULL pointer check */
  for (ind = 0; ind < m_forman_cbi_a2_size; ++ind)
    m_forman_cbi_a2[ind] = 4;
  return m_forman_cbi_a2;
}

static int * forman_cbi_a3(int m_dim, int m_forman_cbi_a3_size,
                           const int * m_cn, const mesh * m)
{
  int i, ind, j, j_loc, p, q, r;
  int * m_forman_cbi_a3;
  jagged1 m_cf_p_r_i, m_cfn_p_r;
  jagged2 m_cf_p_r;
  
  m_forman_cbi_a3 = (int *) malloc(m_forman_cbi_a3_size * sizeof(int));
  /* NULL pointer check */
  ind = 0;
  /* q = 0 */
  for (p = 0; p <= m_dim; ++p)
    for (i = 0; i < m_cn[p]; ++i)
    {
      list_set_4_values(m_forman_cbi_a3 + ind, p, i, p, i);
      ind += 4;
    }
  /* q > 0 */
  for (q = 1; q <= m_dim; ++q)
    for (p = q; p <= m_dim; ++p)
    {
      r = p - q;
      mesh_cfn_part2(&m_cfn_p_r, m, p, r);
      mesh_cf_part2(&m_cf_p_r, m, p, r);
      for (i = 0; i < m_cn[p]; ++i)
      {
        jagged2_part1(&m_cf_p_r_i, &m_cf_p_r, i);
        for (j_loc = 0; j_loc < m_cfn_p_r.a1[i]; ++j_loc)
        {
          j = jagged1_part1(&m_cf_p_r_i, j_loc);
          list_set_4_values(m_forman_cbi_a3 + ind, p, i, r, j);
          ind += 4;
        }
      }
    }
  return m_forman_cbi_a3;
}

jagged3 * forman_cbi(const mesh * m, const int * m_forman_cn)
{
  int m_dim, m_forman_cbi_a2_size, m_forman_cbi_a3_size;
  int * m_cn, * m_forman_cbi_a1, * m_forman_cbi_a2, * m_forman_cbi_a3;
  jagged3 * m_forman_cbi;

  m_dim = m->dim;
  m_cn = m->cn;
  m_forman_cbi = (jagged3 *) malloc(sizeof(jagged3));
  /* NULL pointer check */
  m_forman_cbi_a1 = forman_cbi_a1(m_dim, m_forman_cn);
  /* NULL pointer check */
  m_forman_cbi_a2_size = list_sum(m_forman_cbi_a1, 0, m_dim + 1);
  m_forman_cbi_a2 = forman_cbi_a2(m_forman_cbi_a2_size);
  /* NULL pointer check */
  m_forman_cbi_a3_size = list_sum(m_forman_cbi_a2, 0, m_forman_cbi_a2_size);
  m_forman_cbi_a3 = forman_cbi_a3(m_dim, m_forman_cbi_a3_size, m_cn, m);
  /* NULL pointer check */
  jagged3_set(m_forman_cbi, m_dim + 1, m_forman_cbi_a1, m_forman_cbi_a2,
              m_forman_cbi_a3);
  return m_forman_cbi;
}
