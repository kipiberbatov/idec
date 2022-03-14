#include <stdlib.h>
#include "forman_private.h"
#include "list.h"

static int * forman_fi_a1(int m_dim)
{
  int q_f;
  int * m_forman_fi_a1;
  
  m_forman_fi_a1 = (int *) malloc((m_dim + 1) * sizeof(int));
  /* NULL pointer check */
  for (q_f = 0; q_f <= m_dim; ++q_f)
    m_forman_fi_a1[q_f] = m_dim - q_f + 2;
  return m_forman_fi_a1;
}

static int * forman_fi_a2(
  const mesh * m, int m_dim, const int * m_cn, int m_forman_fi_a2_size)
{
  int i, ind, p_f, q_f, r_f, s;
  int * m_forman_fi_a2;
  
  m_forman_fi_a2 = (int *) calloc(m_forman_fi_a2_size, sizeof(int));
  /* NULL pointer check */
  ind = 0;
  for (q_f = 0; q_f <= m_dim; ++q_f)
    for (s = 0; s <= m_dim - q_f + 1; ++s)
    {
      for (p_f = q_f; p_f <= q_f + s - 1; ++p_f)
      {
        r_f = p_f - q_f;
        for (i = 0; i < m_cn[p_f]; ++i)
          m_forman_fi_a2[ind] += mesh_cfn_part3(m, p_f, r_f, i);
      }
      ++ind;
    }
  return m_forman_fi_a2;
}

jagged2 * forman_fi(const mesh * m)
{
  int m_dim, m_forman_fi_a2_size;
  int * m_cn, * m_forman_fi_a1, * m_forman_fi_a2;
  jagged2 * m_forman_fi;
  
  m_dim = m->dim;
  m_cn = m->cn;
  m_forman_fi = (jagged2 *) malloc(sizeof(jagged2));
  /* NULL pointer check */
  m_forman_fi_a1 = forman_fi_a1(m_dim);
  /* NULL pointer check */
  m_forman_fi_a2_size = list_sum(m_forman_fi_a1, 0, m_dim + 1);
  m_forman_fi_a2 = forman_fi_a2(m, m_dim, m_cn, m_forman_fi_a2_size);
  /* NULL pointer check */
  jagged2_set(m_forman_fi, m_dim + 1, m_forman_fi_a1, m_forman_fi_a2);
  return m_forman_fi;
}
