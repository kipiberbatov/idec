#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "forman_private.h"
#include "int.h"

static int add_so_far(const mesh * m, int q_f, int r)
{
  int n = 0, t;
  jagged1 m_cfn_qft_t;

  if (q_f == 0)
  {
    for (t = 0; t < r; ++t)
      n += m->cn[t];
  }
  else
  {
    for (t = 0; t < r; ++t)
    {
      mesh_cfn_part2(&m_cfn_qft_t, m, q_f + t, t);
      n += int_array_total_sum(m_cfn_qft_t.a0, m_cfn_qft_t.a1);
    }
  }
  return n;
}

static int flatten(const mesh * m, int q_f, int r, int j, int k_local)
{
  int j0, n = 0;
  jagged1 m_cfn_q_r;
  
  n = add_so_far(m, q_f, r);

  if (q_f == 0)
    n += j;
  else
  {
    mesh_cfn_part2(&m_cfn_q_r, m, q_f + r, r);
    for (j0 = 0; j0 < j; ++j0)
      n += m_cfn_q_r.a1[j0];
    n += k_local;
  }
  return n;
}

void forman_cf_a4(int * m_forman_cf_a4, const mesh * m)
{
  int d;
  int index;
  int p_f, q_f;
  int p, q, r, s;
  int i, j, k, l;
  int j_local, k_local, l_local;
  int * m_cn;
  jagged1 m_cf_p_q_i;
  jagged1 m_cf_p_s_i;
  jagged1 m_cf_q_r_j;
  jagged1 m_cf_q_s_j;
  jagged1 m_cf_r_s_k;
  jagged2 m_cf_p_s;

  d = m->dim;
  m_cn = m->cn;

  index = 0;
  for (p_f = 1; p_f <= d; ++p_f)
  {
    for (q_f = 0; q_f < p_f; ++q_f)
    {
      for (p = p_f; p <= d; ++p)
      {
        s = p - p_f;
        mesh_cf_part2(&m_cf_p_s, m, p, s);
        for (i = 0; i < m_cn[p]; ++i)
        {
          jagged2_part1(&m_cf_p_s_i, &m_cf_p_s, i);
          for (l_local = 0; l_local < m_cf_p_s_i.a0; ++l_local)
          {
            l = m_cf_p_s_i.a1[l_local];
            for (q = q_f + s; q <= p; ++q)
            {
              r = q - q_f;
              mesh_cf_part3(&m_cf_p_q_i, m, p, q, i);
              for (j_local = 0; j_local < m_cf_p_q_i.a0; ++j_local)
              {
                j = m_cf_p_q_i.a1[j_local];
                mesh_cf_part3(&m_cf_q_s_j, m, q, s, j);
                if (!jagged1_member(&m_cf_q_s_j, l))
                  continue;
                mesh_cf_part3(&m_cf_q_r_j, m, q, r, j);
                for (k_local = 0; k_local < m_cf_q_r_j.a0; ++k_local)
                {
                  k = m_cf_q_r_j.a1[k_local];
                  mesh_cf_part3(&m_cf_r_s_k, m, r, s, k);
                  if (jagged1_member(&m_cf_r_s_k, l))
                  {
                    m_forman_cf_a4[index] = flatten(m, q_f, r, j, k_local);
                    ++index;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}
