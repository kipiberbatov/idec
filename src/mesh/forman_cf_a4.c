#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "forman_private.h"
#include "int.h"


/* q_f = 0 => p >= q = r >= s*/
static void forman_cf_a4_level_3_zero(int * m_forman_cf_a4, int * index,
  const mesh * m, const jagged2 * m_cf_p_s, int p, int m_cn_p, int s)
{
  int q;
  int i, j,       l;
  int    j_local, l_local;
  int m_cn_up_to_q;
  int * m_cn;
  jagged1 m_cf_p_q_i, m_cf_p_s_i, m_cf_q_s_j;
  jagged2                         m_cf_q_s;

  m_cn = m->cn;
  for (i = 0; i < m_cn_p; ++i)
  {
    jagged2_part1(&m_cf_p_s_i, m_cf_p_s, i);
    for (l_local = 0; l_local < m_cf_p_s_i.a0; ++l_local)
    {
      l = m_cf_p_s_i.a1[l_local];
      
      /* c(p, i) > c(q, j) = c(r, k) = c(s, l) */
      m_forman_cf_a4[*index] = int_array_total_sum(s, m->cn) + l;
      ++*index;
      
      /* c(p, i) > c(q, j) = c(r, k) > c(s, l) */
      for (q = s + 1; q < p; ++q)
      {
        m_cn_up_to_q = int_array_total_sum(q, m_cn);
        mesh_cf_part3(&m_cf_p_q_i, m, p, q, i);
        mesh_cf_part2(&m_cf_q_s, m, q, s);
        for (j_local = 0; j_local < m_cf_p_q_i.a0; ++j_local)
        {
          j = m_cf_p_q_i.a1[j_local];
          jagged2_part1(&m_cf_q_s_j, &m_cf_q_s, j);
          /* add forman cell when c(q, j) > c(s, l) */
          if (jagged1_member(&m_cf_q_s_j, l))
          {
            m_forman_cf_a4[*index] = m_cn_up_to_q + j;
            ++*index;
          }
        }
      }
      
      /* c(p, i) = c(q, j) = c(r, k) > c(s, l) */
      m_forman_cf_a4[*index] = int_array_total_sum(p, m_cn) + i;
      ++*index;
    }
  }
}

static int add_so_far_nonzero(const mesh * m, int q_f, int r)
{
  int n, t;
  jagged1 m_cfn_qft_t;

  n = 0;
  for (t = 0; t < r; ++t)
  {
    mesh_cfn_part2(&m_cfn_qft_t, m, q_f + t, t);
    n += int_array_total_sum(m_cfn_qft_t.a0, m_cfn_qft_t.a1);
  }
  return n;
}

/* q_f > 0 => p >= q > r >= s */
static void forman_cf_a4_level_3_nonzero(int * m_forman_cf_a4, int * index,
  const mesh * m, const jagged2 * m_cf_p_s, int p, int m_cn_p, int s, int q_f)
{
  int q, r;
  int i, j,       k,       l;
  int    j_local, k_local, l_local;
  int so_far, so_far_global, so_far_local;
  jagged1 m_cfn_q_r;
  jagged1 m_cf_p_q_i, m_cf_p_s_i, m_cf_q_r_j, m_cf_q_s_j, m_cf_r_s_k;
  jagged2                         m_cf_q_r,   m_cf_q_s,   m_cf_r_s;

  for (i = 0; i < m_cn_p; ++i)
  {
    jagged2_part1(&m_cf_p_s_i, m_cf_p_s, i);
    for (l_local = 0; l_local < m_cf_p_s_i.a0; ++l_local)
    {
      l = m_cf_p_s_i.a1[l_local];
      
      /* c(p, i) > c(q, j) > c(r, k) = c(s, l) */
      q = q_f + s;
      mesh_cfn_part2(&m_cfn_q_r, m, q, s);
      so_far_global = add_so_far_nonzero(m, q_f, s);
      mesh_cf_part3(&m_cf_p_q_i, m, p, q, i);
      
      mesh_cf_part2(&m_cf_q_s, m, q, s);
      for (j_local = 0; j_local < m_cf_p_q_i.a0; ++j_local)
      {
        j = m_cf_p_q_i.a1[j_local];
        jagged2_part1(&m_cf_q_s_j, &m_cf_q_s, j);
        /* add forman cell when c(q, j) > c(r, k) = c(s, l) */
        if (jagged1_member(&m_cf_q_s_j, l))
        {
          so_far_local = int_array_total_sum(j, m_cfn_q_r.a1);
          so_far = so_far_global + so_far_local;
          k_local = jagged1_position(&m_cf_q_s_j, l);
          m_forman_cf_a4[*index] = so_far + k_local;
          ++*index;
        }
      }

      /* c(p, i) > c(q, j) > c(r, k) > c(s, l) */
      for (q = q_f + s + 1; q < p; ++q)
      {
        r = q - q_f;
        mesh_cf_part2(&m_cf_q_s, m, q, s);
        mesh_cf_part2(&m_cf_q_r, m, q, r);
        mesh_cf_part2(&m_cf_r_s, m, r, s);
        so_far_global = add_so_far_nonzero(m, q_f, r);
        mesh_cfn_part2(&m_cfn_q_r, m, q, r);

        mesh_cf_part3(&m_cf_p_q_i, m, p, q, i);
        for (j_local = 0; j_local < m_cf_p_q_i.a0; ++j_local)
        {
          j = m_cf_p_q_i.a1[j_local];
          jagged2_part1(&m_cf_q_s_j, &m_cf_q_s, j);
          /* check whether c(q, j) > c(s, l) */
          if (!jagged1_member(&m_cf_q_s_j, l))
            continue;
          so_far_local = int_array_total_sum(j, m_cfn_q_r.a1);
          so_far = so_far_global + so_far_local;
          jagged2_part1(&m_cf_q_r_j, &m_cf_q_r, j);
          for (k_local = 0; k_local < m_cf_q_r_j.a0; ++k_local)
          {
            k = m_cf_q_r_j.a1[k_local];
            jagged2_part1(&m_cf_r_s_k, &m_cf_r_s, k);
            /* add forman cell when c(r, k) > c(s, l) */
            if (jagged1_member(&m_cf_r_s_k, l))
            {
              m_forman_cf_a4[*index] = so_far + k_local;
              ++*index;
            }
          }
        }
      }

      /* c(p, i) = c(q, j) > c(r, k) > c(s, l) */
      q = p;
      r = q - q_f;
      j = i;
      so_far_global = add_so_far_nonzero(m, q_f, r);
      mesh_cfn_part2(&m_cfn_q_r, m, q, r);
      so_far_local = int_array_total_sum(j, m_cfn_q_r.a1);
      so_far = so_far_global + so_far_local;
      mesh_cf_part3(&m_cf_q_r_j, m, q, r, j);
      mesh_cf_part2(&m_cf_r_s, m, r, s);
      for (k_local = 0; k_local < m_cf_q_r_j.a0; ++k_local)
      {
        k = m_cf_q_r_j.a1[k_local];
        jagged2_part1(&m_cf_r_s_k, &m_cf_r_s, k);
        /* add forman cell when c(r, k) > c(s, l) */
        if (jagged1_member(&m_cf_r_s_k, l))
        {
          m_forman_cf_a4[*index] = so_far + k_local;
          ++*index;
        }
      }
    }
  }
}

void forman_cf_a4(int * m_forman_cf_a4, const mesh * m)
{
  int d;
  int index;
  int p_f, q_f;
  int p, s;
  int m_cn_p;
  int * m_cn;
  jagged2 m_cf_p_s;

  d = m->dim;
  m_cn = m->cn;
  index = 0;
  
  for (p_f = 1; p_f <= d; ++p_f)
  {
    for (p = p_f; p <= d; ++p)
    {
      m_cn_p = m_cn[p];
      s = p - p_f;
      mesh_cf_part2(&m_cf_p_s, m, p, s);
      forman_cf_a4_level_3_zero(m_forman_cf_a4, &index,
                                m, &m_cf_p_s, p, m_cn_p, s);
    }
    for (q_f = 1; q_f < p_f; ++q_f)
    {
      for (p = p_f; p <= d; ++p)
      {
        m_cn_p = m_cn[p];
        s = p - p_f;
        mesh_cf_part2(&m_cf_p_s, m, p, s);
        forman_cf_a4_level_3_nonzero(m_forman_cf_a4, &index,
                                     m, &m_cf_p_s, p, m_cn_p, s, q_f);
      }
    }
  }
}
