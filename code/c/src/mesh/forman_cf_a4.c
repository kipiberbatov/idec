#include "forman_private.h"
#include "int.h"


static void forman_cf_a4_level_5_zero_middle(
  int * m_forman_cf_a4, int * index,
  const mesh * m, int p, int s, int * m_cn, int i, int l)
{
  int j, j_local, m_cn_up_to_q, q;
  jagged1 m_cf_p_q_i, m_cf_q_s_j;
  jagged2 m_cf_q_s;

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
}

/* q_f = 0 => p >= q = r >= s*/
static void forman_cf_a4_level_3_zero(int * m_forman_cf_a4, int * index,
  const mesh * m, const jagged2 * m_cf_p_s, int p, int s)
{
  int i, l_local, l, m_cf_p_s_a1_i, m_cn_p, m_cn_up_to_p, m_cn_up_to_s;
  int * m_cf_p_s_a1, * m_cf_p_s_i, * m_cn;

  m_cn = m->cn;
  m_cn_p = m_cn[p];
  m_cn_up_to_p = int_array_total_sum(p, m_cn);
  m_cn_up_to_s = int_array_total_sum(s, m_cn);
  m_cf_p_s_a1 = m_cf_p_s->a1;
  m_cf_p_s_i = m_cf_p_s->a2;
  for (i = 0; i < m_cn_p; ++i)
  {
    m_cf_p_s_a1_i = m_cf_p_s_a1[i];
    for (l_local = 0; l_local < m_cf_p_s_a1_i; ++l_local)
    {
      l = m_cf_p_s_i[l_local];

      /* c(p, i) > c(q, j) = c(r, k) = c(s, l) */
      m_forman_cf_a4[*index] = m_cn_up_to_s + l;
      ++*index;

      /* c(p, i) > c(q, j) = c(r, k) > c(s, l) */
      forman_cf_a4_level_5_zero_middle(m_forman_cf_a4, index,
        m, p, s, m_cn, i, l);

      /* c(p, i) = c(q, j) = c(r, k) > c(s, l) */
      m_forman_cf_a4[*index] = m_cn_up_to_p + i;
      ++*index;
    }
    m_cf_p_s_i += m_cf_p_s_a1_i;
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

static void
forman_cf_a4_level_5_nonzero_begin(int * m_forman_cf_a4, int * index,
  const mesh * m, int p, int s, int q_f, int i, int l)
{
  int j, j_local, k_local, q, so_far, so_far_global, so_far_local;
  jagged1 m_cf_p_q_i, m_cf_q_s_j, m_cfn_q_r;
  jagged2 m_cf_q_s;

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
}

static void
forman_cf_a4_level_5_nonzero_middle(int * m_forman_cf_a4, int * index,
  const mesh * m, int p, int s, int q_f, int i, int l)
{
  int j, j_local, k, k_local, q, r, so_far, so_far_global, so_far_local;
  jagged1 m_cf_p_q_i, m_cf_q_r_j, m_cf_q_s_j, m_cf_r_s_k, m_cfn_q_r;
  jagged2 m_cf_q_r, m_cf_q_s, m_cf_r_s;

  for (q = q_f + s + 1; q < p; ++q)
  {
    r = q - q_f;
    mesh_cf_part2(&m_cf_q_r, m, q, r);
    mesh_cf_part2(&m_cf_q_s, m, q, s);
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
}

static void
forman_cf_a4_level_5_nonzero_end(int * m_forman_cf_a4, int * index,
  const mesh * m, int p, int s, int q_f, int i, int l)
{
  int j, k_local, k, q, r, so_far, so_far_global, so_far_local;
  jagged1 m_cf_q_r_j, m_cf_r_s_k, m_cfn_q_r;
  jagged2 m_cf_r_s;

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

/* q_f > 0 => p >= q > r >= s */
static void forman_cf_a4_level_3_nonzero(int * m_forman_cf_a4, int * index,
  const mesh * m, const jagged2 * m_cf_p_s, int p, int s, int q_f)
{
  int i, l, l_local, m_cf_p_s_a1_i, m_cn_p;
  int * m_cf_p_s_a1, * m_cf_p_s_i;

  m_cn_p = m_cf_p_s->a0;
  m_cf_p_s_a1 = m_cf_p_s->a1;
  m_cf_p_s_i = m_cf_p_s->a2;
  for (i = 0; i < m_cn_p; ++i)
  {
    m_cf_p_s_a1_i = m_cf_p_s_a1[i];
    for (l_local = 0; l_local < m_cf_p_s_a1_i; ++l_local)
    {
      l = m_cf_p_s_i[l_local];

      /* c(p, i) > c(q, j) > c(r, k) = c(s, l) */
      forman_cf_a4_level_5_nonzero_begin(m_forman_cf_a4, index,
        m, p, s, q_f, i, l);

      /* c(p, i) > c(q, j) > c(r, k) > c(s, l) */
      forman_cf_a4_level_5_nonzero_middle(m_forman_cf_a4, index,
        m, p, s, q_f, i, l);

      /* c(p, i) = c(q, j) > c(r, k) > c(s, l) */
      forman_cf_a4_level_5_nonzero_end(m_forman_cf_a4, index,
        m, p, s, q_f, i, l);
    }
    m_cf_p_s_i += m_cf_p_s_a1_i;
  }
}

void forman_cf_a4(int * m_forman_cf_a4, const mesh * m)
{
  int d, index, p, p_f, q_f, s;
  jagged2 m_cf_p_s;

  d = m->dim;
  index = 0;

  for (p_f = 1; p_f <= d; ++p_f)
  {
    /* q_f = 0 */
    for (p = p_f; p <= d; ++p)
    {
      s = p - p_f;
      mesh_cf_part2(&m_cf_p_s, m, p, s);
      forman_cf_a4_level_3_zero(m_forman_cf_a4, &index, m, &m_cf_p_s, p, s);
    }
    /* q_f > 0 */
    for (q_f = 1; q_f < p_f; ++q_f)
    {
      for (p = p_f; p <= d; ++p)
      {
        s = p - p_f;
        mesh_cf_part2(&m_cf_p_s, m, p, s);
        forman_cf_a4_level_3_nonzero(m_forman_cf_a4, &index,
                                     m, &m_cf_p_s, p, s, q_f);
      }
    }
  }
}
