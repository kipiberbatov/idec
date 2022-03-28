#include <errno.h>
#include <stdlib.h>
#include "forman_private.h"
#include "int.h"

static void forman_fi_a1(int * m_forman_fi_a1, int m_dim)
{
  int q_f;
  
  for (q_f = 0; q_f <= m_dim; ++q_f)
    m_forman_fi_a1[q_f] = m_dim - q_f + 2;
}

static void forman_fi_a2(int * m_forman_fi_a2, const mesh * m)
{
  int ind, m_dim, p_f, q_f, r_f, s;
  int * m_cn;
  jagged1 m_cfn_p_f_r_f;

  m_dim = m->dim;
  m_cn = m->cn;

  ind = 0;

  /* q_f = 0 */
  for (s = 0; s <= m_dim + 1; ++s)
  {
    for (p_f = 0; p_f <= s - 1; ++p_f)
      m_forman_fi_a2[ind] += m_cn[p_f];
    ++ind;
  }

  /* q_f > 0 */
  for (q_f = 1; q_f <= m_dim; ++q_f)
  {
    for (s = 0; s <= m_dim - q_f + 1; ++s)
    {
      for (p_f = q_f; p_f <= q_f + s - 1; ++p_f)
      {
        r_f = p_f - q_f;
        mesh_cfn_part2(&m_cfn_p_f_r_f, m, p_f, r_f);
        m_forman_fi_a2[ind] += jagged1_total_sum(&m_cfn_p_f_r_f);
      }
      ++ind;
    }
  }
}

jagged2 * forman_fi(const mesh * m)
{
  int m_forman_fi_a2_size;
  jagged2 * m_forman_fi;
  
  m_forman_fi = (jagged2 *) malloc(sizeof(jagged2));
  if (errno)
  {
    perror("forman_fi - cannot allocate memory for m_forman_fi");
    goto end;
  }
  
  m_forman_fi->a0 = m->dim + 1;
  m_forman_fi->a1 = (int *) malloc(sizeof(int) * m_forman_fi->a0);
  forman_fi_a1(m_forman_fi->a1, m->dim);
  if (errno)
  {
    perror("forman_fi - cannot allocate memory for m_forman_fi->a1");
    goto m_forman_fi_free;
  }
  
  m_forman_fi_a2_size = int_array_total_sum(m->dim + 1, m_forman_fi->a1);
  m_forman_fi->a2 = (int *) calloc(m_forman_fi_a2_size, sizeof(int));
  forman_fi_a2(m_forman_fi->a2, m);
  if (errno)
  {
    perror("forman_fi - cannot allocate memory for m_forman_fi->a2");
    goto m_forman_fi_a1_free;
  }
  
  return m_forman_fi;
  
  /* cleaning if an error occurs */
m_forman_fi_a1_free:
  free(m_forman_fi->a1);
m_forman_fi_free:
  free(m_forman_fi);
end:
  return NULL;
}
