#include <stdlib.h>
#include "forman_private.h"
#include "list.h"

static int * forman_si_a1(int m_dim)
{
  int r;
  int * m_forman_si_a1;
  
  m_forman_si_a1 = (int *) malloc((m_dim + 1) * sizeof(int));
   /* NULL pointer check */
  for (r = 0; r <= m_dim; ++r)
    m_forman_si_a1[r] = r + 1;
  return m_forman_si_a1;
}

static int * forman_si_a2(int m_dim, const int * m_cn, int m_forman_si_a2_size)
{
  int ind, m_cn_r, r, s;
  int * m_forman_si_a2;
  
  m_forman_si_a2 = (int *) malloc(m_forman_si_a2_size * sizeof(int));
  /* NULL pointer check */
  ind = 0;
  for (r = 0; r <= m_dim; ++r)
  {
    m_cn_r = m_cn[r];
    for(s = 0; s <= r; ++s)
    {
      m_forman_si_a2[ind] = m_cn_r;
      ++ind;
    }
  }
  return m_forman_si_a2;
}

static int * forman_si_a3(
  const mesh * m, int m_dim, const int * m_cn, int m_forman_si_a3_size)
{
  int i, ind, k, m_cn_r, r, s;
  int * m_forman_si_a3;
  
  m_forman_si_a3 = (int *) calloc(m_forman_si_a3_size, sizeof(int));
  /* NULL pointer check */
  ind = 0;
  for (r = 0; r <= m_dim; ++r)
  {
    m_cn_r = m_cn[r];
    for(s = 0; s <= r; ++s)
      for (k = 0; k < m_cn_r; ++k)
      {
        for (i = 0; i < k; ++i)
          m_forman_si_a3[ind] += mesh_cfn_part3(m, r, s, i);
        ++ind;
      }
  }
  return m_forman_si_a3;
}

jagged3 * forman_si(const mesh * m)
{
  int m_dim, m_forman_si_a2_size, m_forman_si_a3_size;
  int * m_cn, * m_forman_si_a1, * m_forman_si_a2, * m_forman_si_a3;
  jagged3 * m_forman_si;

  m_dim = m->dim;
  m_cn = m->cn;
  m_forman_si = (jagged3 *) malloc(sizeof(jagged3));
  /* NULL pointer check */
  m_forman_si_a1 = forman_si_a1(m_dim);
  /* NULL pointer check */
  m_forman_si_a2_size = list_sum(m_forman_si_a1, 0, m_dim + 1);
  m_forman_si_a2 = forman_si_a2(m_dim, m_cn, m_forman_si_a2_size);
  /* NULL pointer check */
  m_forman_si_a3_size = list_sum(m_forman_si_a2, 0, m_forman_si_a2_size);
  m_forman_si_a3 = forman_si_a3(m, m_dim, m_cn, m_forman_si_a3_size);
  jagged3_set(m_forman_si, m_dim + 1, m_forman_si_a1, m_forman_si_a2,
              m_forman_si_a3);
  return m_forman_si;
}
