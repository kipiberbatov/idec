#include "forman_private.h"
#include "int.h"

/* q_f = 0 => p >= q = r >= s*/
static void forman_cf_a3_level_3_zero(int * m_forman_cf_a3, int * index,
  const mesh * m, const jagged2 * m_cf_p_s, int p, int m_cn_p, int s)
{
  int q;
  int i, j,       l;
  int    j_local, l_local;
  jagged1 m_cf_p_q_i, m_cf_p_s_i, m_cf_q_s_j;
  jagged2                         m_cf_q_s;

  for (i = 0; i < m_cn_p; ++i)
  {
    jagged2_part1(&m_cf_p_s_i, m_cf_p_s, i);
    for (l_local = 0; l_local < m_cf_p_s_i.a0; ++l_local)
    {
      l = m_cf_p_s_i.a1[l_local];
      m_forman_cf_a3[*index] = 0;
      
      /* c(p, i) > c(q, j) = c(r, k) = c(s, l) */
      ++m_forman_cf_a3[*index];
      
      /* c(p, i) > c(q, j) = c(r, k) > c(s, l) */
      for (q = s + 1; q < p; ++q)
      {
        mesh_cf_part3(&m_cf_p_q_i, m, p, q, i);
        mesh_cf_part2(&m_cf_q_s, m, q, s);
        for (j_local = 0; j_local < m_cf_p_q_i.a0; ++j_local)
        {
          j = m_cf_p_q_i.a1[j_local];
          jagged2_part1(&m_cf_q_s_j, &m_cf_q_s, j);
          /* increment if c(q, j) > c(s, l) */
          if (jagged1_member(&m_cf_q_s_j, l))
            ++m_forman_cf_a3[*index];
        }
      }
      
      /* c(p, i) = c(q, j) = c(r, k) > c(s, l) */
      ++m_forman_cf_a3[*index];
      
      ++*index;
    }
  }
}

/* q_f > 0 => p >= q > r >= s */
static void forman_cf_a3_level_3_nonzero(int * m_forman_cf_a3, int * index,
  const mesh * m, const jagged2 * m_cf_p_s, int p, int m_cn_p, int s, int q_f)
{
  int q, r;
  int i, j,       k,       l;
  int    j_local, k_local, l_local;
  jagged1 m_cf_p_q_i, m_cf_p_s_i, m_cf_q_r_j, m_cf_q_s_j, m_cf_r_s_k;
  jagged2                         m_cf_q_r,   m_cf_q_s,   m_cf_r_s;

  for (i = 0; i < m_cn_p; ++i)
  {
    jagged2_part1(&m_cf_p_s_i, m_cf_p_s, i);
    for (l_local = 0; l_local < m_cf_p_s_i.a0; ++l_local)
    {
      l = m_cf_p_s_i.a1[l_local];
      m_forman_cf_a3[*index] = 0;
      
      /* c(p, i) > c(q, j) > c(r, k) = c(s, l) */
      q = q_f + s;
      mesh_cf_part3(&m_cf_p_q_i, m, p, q, i);
      mesh_cf_part2(&m_cf_q_s, m, q, s);
      for (j_local = 0; j_local < m_cf_p_q_i.a0; ++j_local)
      {
        j = m_cf_p_q_i.a1[j_local];
        jagged2_part1(&m_cf_q_s_j, &m_cf_q_s, j);
        /* increment if c(q, j) > c(s, l) */
        if (jagged1_member(&m_cf_q_s_j, l))
          ++m_forman_cf_a3[*index];
      }

      /* c(p, i) > c(q, j) > c(r, k) > c(s, l) */
      for (q = q_f + s + 1; q < p; ++q)
      {
        r = q - q_f;
        mesh_cf_part2(&m_cf_q_s, m, q, s);
        mesh_cf_part2(&m_cf_q_r, m, q, r);
        mesh_cf_part2(&m_cf_r_s, m, r, s);

        mesh_cf_part3(&m_cf_p_q_i, m, p, q, i);
        for (j_local = 0; j_local < m_cf_p_q_i.a0; ++j_local)
        {
          j = m_cf_p_q_i.a1[j_local];
          jagged2_part1(&m_cf_q_s_j, &m_cf_q_s, j);
          /* check whether c(q, j) > c(s, l) */
          if (!jagged1_member(&m_cf_q_s_j, l))
            continue;
          jagged2_part1(&m_cf_q_r_j, &m_cf_q_r, j);
          for (k_local = 0; k_local < m_cf_q_r_j.a0; ++k_local)
          {
            k = m_cf_q_r_j.a1[k_local];
            jagged2_part1(&m_cf_r_s_k, &m_cf_r_s, k);
            /* increment if c(r, k) > c(s, l) */
            if (jagged1_member(&m_cf_r_s_k, l))
              ++m_forman_cf_a3[*index];
          }
        }
      }

      /* c(p, i) = c(q, j) > c(r, k) > c(s, l) */
      q = p;
      r = q - q_f;
      j = i;
      mesh_cf_part3(&m_cf_q_r_j, m, q, r, j);
      mesh_cf_part2(&m_cf_r_s, m, r, s);
      for (k_local = 0; k_local < m_cf_q_r_j.a0; ++k_local)
      {
        k = m_cf_q_r_j.a1[k_local];
        jagged2_part1(&m_cf_r_s_k, &m_cf_r_s, k);
        /* increment if c(r, k) > c(s, l) */
        if (jagged1_member(&m_cf_r_s_k, l))
          ++m_forman_cf_a3[*index];
      }
      
      ++*index;
    }
  }
}

void
forman_cf_a3(int * m_forman_cf_a3, const mesh * m, const int * m_forman_cn)
{
  int d;
  int index;
  int p_f, q_f, pf_minus_qf;
  int p, s;
  int m_cn_p;
  int m_forman_cn_pf;
  int subfaces_total;
  int * m_cn;
  jagged2 m_cf_p_s;

  d = m->dim;
  m_cn = m->cn;
  index = 0;

  /* all 1-cells are edges, all 2-cells are quadrilaterals */
  for (p_f = 1; p_f <= 2; ++p_f)
  {
    m_forman_cn_pf = m_forman_cn[p_f];
    for (q_f = 0; q_f < p_f; ++q_f)
    {
      pf_minus_qf = p_f - q_f;
      subfaces_total = (1 << pf_minus_qf) * int_binomial(p_f, pf_minus_qf);
      int_array_assign_constant(m_forman_cf_a3 + index, m_forman_cn_pf,
                                subfaces_total);
      index += m_forman_cn_pf;
    }
  }
  
  /* in general, higher-order cells may not be quasi-cubes */
  for (p_f = 3; p_f <= d; ++p_f)
  {
    for (p = p_f; p <= d; ++p)
    {
      m_cn_p = m_cn[p];
      s = p - p_f;
      mesh_cf_part2(&m_cf_p_s, m, p, s);
      forman_cf_a3_level_3_zero(m_forman_cf_a3, &index,
                                m, &m_cf_p_s, p, m_cn_p, s);
    }
    for (q_f = 1; q_f < p_f; ++q_f)
    {
      for (p = p_f; p <= d; ++p)
      {
        m_cn_p = m_cn[p];
        s = p - p_f;
        mesh_cf_part2(&m_cf_p_s, m, p, s);
        forman_cf_a3_level_3_nonzero(m_forman_cf_a3, &index,
                                    m, &m_cf_p_s, p, m_cn_p, s, q_f);
      }
    }
  }
}
