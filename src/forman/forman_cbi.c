#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "forman_private.h"
#include "int.h"

static void forman_cbi_a3(int * m_forman_cbi_a3, const mesh * m)
{
  int i, ind, j, j_loc, m_dim, p, q, r;
  int * m_cn;
  jagged1 m_cf_p_r_i, m_cfn_p_r;
  jagged2 m_cf_p_r;
  
  m_dim = m->dim;
  m_cn = m->cn;
  
  ind = 0;
  
  /* q = 0 */
  for (p = 0; p <= m_dim; ++p)
  {
    for (i = 0; i < m_cn[p]; ++i)
    {
      int_array_4_values_set(m_forman_cbi_a3 + ind, p, i, p, i);
      ind += 4;
    }
  }
  
  /* q > 0 */
  for (q = 1; q <= m_dim; ++q)
  {
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
          int_array_4_values_set(m_forman_cbi_a3 + ind, p, i, r, j);
          ind += 4;
        }
      }
    }
  }
}

jagged3 * forman_cbi(const mesh * m, const int * m_forman_cn)
{
  int m_forman_cbi_a2_size, m_forman_cbi_a3_size;
  jagged3 * m_forman_cbi;

  m_forman_cbi = (jagged3 *) malloc(sizeof(jagged3));
  if (errno)
  {
    perror("forman_cbi - cannot allocate memory for m_forman_cbi");
    goto end;
  }
  
  m_forman_cbi->a0 = m->dim + 1;
  m_forman_cbi->a1 = (int *) malloc(sizeof(int) * (m->dim + 1));
  if (errno)
  {
    perror("forman_cbi_a1 - cannot allocate memory for m_forman_cbi->a1");
    goto m_forman_cbi_free;
  }
  memcpy(m_forman_cbi->a1, m_forman_cn, sizeof(int) * (m->dim + 1));
  
  m_forman_cbi_a2_size = int_array_total_sum(m->dim + 1, m_forman_cbi->a1);
  m_forman_cbi->a2 = (int *) malloc(sizeof(int) * m_forman_cbi_a2_size);
  if (errno)
  {
    perror("forman_cbi_a2 - cannot allocate memory for m_forman_cbi->a2");
    goto m_forman_cbi_a1_free;
  }
  int_array_assign_constant(m_forman_cbi->a2, m_forman_cbi_a2_size, 4);
  
  m_forman_cbi_a3_size = 
    int_array_total_sum(m_forman_cbi_a2_size, m_forman_cbi->a2);
  m_forman_cbi->a3 = (int *) malloc(sizeof(int) * m_forman_cbi_a3_size);
  if (errno)
  {
    perror("forman_cbi_a3 - cannot allocate memory for m_forman_cbi->a3");
    goto m_forman_cbi_a2_free;
  }
  forman_cbi_a3(m_forman_cbi->a3, m);
  
  return m_forman_cbi;

  /* cleaning if an error occurs */
m_forman_cbi_a2_free:
  free(m_forman_cbi->a2);
m_forman_cbi_a1_free:
  free(m_forman_cbi->a1);
m_forman_cbi_free:
  free(m_forman_cbi);
end:
  return NULL;
}
