#include <errno.h>
#include <stdlib.h>
#include "forman_private.h"
#include "int.h"

static void forman_si_a1(int * m_forman_si_a1, int m_dim)
{
  int r;
  
  for (r = 0; r <= m_dim; ++r)
    m_forman_si_a1[r] = r + 1;
}

static void forman_si_a2(
  int * m_forman_si_a2, int m_dim, const int * m_cn, int m_forman_si_a2_size)
{
  int ind, r;
  
  ind = 0;
  for (r = 0; r <= m_dim; ++r)
  {
    int_array_assign_constant(m_forman_si_a2 + ind, r + 1, m_cn[r]);
    ind += (r + 1);
  }
}

static void forman_si_a3(
  int * m_forman_si_a3, const mesh * m, int m_forman_si_a3_size)
{
  int ind, k, m_cn_r, m_dim, r, s;
  int * m_cn;
  jagged1 m_cfn_r_s;
  
  m_dim = m->dim;
  m_cn = m->cn;
  
  ind = 0;
  for (r = 0; r <= m_dim; ++r)
  {
    m_cn_r = m_cn[r];
    
    /* s < r */
    for(s = 0; s < r; ++s)
    {
      mesh_cfn_part2(&m_cfn_r_s, m, r, s);
      for (k = 0; k < m_cn_r; ++k)
      {
        m_forman_si_a3[ind] = int_array_total_sum(k, m_cfn_r_s.a1);
        ++ind;
      }
    }
    
    /* s = r */
    for (k = 0; k < m_cn_r; ++k)
    {
      m_forman_si_a3[ind] += k;
      ++ind;
    }
  }
}

jagged3 * forman_si(const mesh * m)
{
  int m_forman_si_a2_size, m_forman_si_a3_size;
  jagged3 * m_forman_si;

  m_forman_si = (jagged3 *) malloc(sizeof(jagged3));
  if (errno)
  {
    perror("forman_si - cannot allocate memory for m_forman_si");
    goto end;
  }
  
  m_forman_si->a0 = m->dim + 1;
  m_forman_si->a1 = (int *) malloc(sizeof(int) * (m->dim + 1));
  if (errno)
  {
    perror("forman_si - cannot allocate memory for m_forman_si->a1");
    goto m_forman_si_free;
  }
  forman_si_a1(m_forman_si->a1, m->dim);
  
  m_forman_si_a2_size = int_array_total_sum(m->dim + 1, m_forman_si->a1);
  m_forman_si->a2 = (int *) malloc(sizeof(int) * m_forman_si_a2_size);
  if (errno)
  {
    perror("forman_si - cannot allocate memory for m_forman_si->a2");
    goto m_forman_si_a1_free;
  }
  forman_si_a2(m_forman_si->a2, m->dim, m->cn, m_forman_si_a2_size);
  
  m_forman_si_a3_size = 
    int_array_total_sum(m_forman_si_a2_size, m_forman_si->a2);
  m_forman_si->a3 = (int *) calloc(m_forman_si_a3_size, sizeof(int));
  if (errno)
  {
    perror("forman_si_a3 - cannot allocate memory for m_forman_si->a3");
    goto m_forman_si_a2_free;
  }
  forman_si_a3(m_forman_si->a3, m, m_forman_si_a3_size);
  
  return m_forman_si;
  
  /* cleaning if an error occurs */
m_forman_si_a2_free:
  free(m_forman_si->a2);
m_forman_si_a1_free:
  free(m_forman_si->a1);
m_forman_si_free:
  free(m_forman_si);
end:
  return NULL;
}
