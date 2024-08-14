#include "forman_private.h"
#include "int.h"

static void forman_cf_a3_level_5_zero_middle(int * m_forman_cf_a3_index,
  const mesh * m, int p, int s, int i, int l)
{
  int j, j_local, q;
  jagged1 m_cf_p_q_i, m_cf_q_s_j;
  jagged2 m_cf_q_s;

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
        ++*m_forman_cf_a3_index;
    }
  }
}

/* q_f = 0 => p >= q = r >= s*/
static void forman_cf_a3_level_3_zero(int * m_forman_cf_a3, int * index,
  const mesh * m, const jagged2 * m_cf_p_s, int p, int m_cn_p, int s)
{
  int i, l, l_local;
  jagged1 m_cf_p_s_i;

  for (i = 0; i < m_cn_p; ++i)
  {
    jagged2_part1(&m_cf_p_s_i, m_cf_p_s, i);
    for (l_local = 0; l_local < m_cf_p_s_i.a0; ++l_local)
    {
      l = m_cf_p_s_i.a1[l_local];

      /* c(p, i) > c(q, j) = c(r, k) = c(s, l) -- begin
       * c(p, i) = c(q, j) = c(r, k) > c(s, l) -- end
       * total -> 2 subfaces (minimal and maximal)
       */
      m_forman_cf_a3[*index] = 2;

      /* c(p, i) > c(q, j) = c(r, k) > c(s, l) -> add middle subfaces */
      forman_cf_a3_level_5_zero_middle(m_forman_cf_a3 + *index, m, p, s, i, l);

      ++*index;
    }
  }
}

static void forman_cf_a3_level_5_nonzero_begin(int * m_forman_cf_a3_index,
  const mesh * m, int p, int s, int q_f, int i, int l)
{
  int j, j_local, q;
  jagged1 m_cf_p_q_i, m_cf_q_s_j;
  jagged2 m_cf_q_s;

  q = q_f + s;
  mesh_cf_part3(&m_cf_p_q_i, m, p, q, i);
  mesh_cf_part2(&m_cf_q_s, m, q, s);
  for (j_local = 0; j_local < m_cf_p_q_i.a0; ++j_local)
  {
    j = m_cf_p_q_i.a1[j_local];
    jagged2_part1(&m_cf_q_s_j, &m_cf_q_s, j);
    /* increment if c(q, j) > c(s, l) */
    if (jagged1_member(&m_cf_q_s_j, l))
      ++*m_forman_cf_a3_index;
  }
}

static void forman_cf_a3_level_5_nonzero_middle(int * m_forman_cf_a3_index,
  const mesh * m, int p, int s, int q_f, int i, int l)
{
  int j, j_local, k, k_local, q, r;
  jagged1 m_cf_p_q_i, m_cf_q_r_j, m_cf_q_s_j, m_cf_r_s_k;
  jagged2 m_cf_q_r,   m_cf_q_s,   m_cf_r_s;

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
          ++*m_forman_cf_a3_index;
      }
    }
  }
}

static void forman_cf_a3_level_5_nonzero_end(int * m_forman_cf_a3_index,
  const mesh * m, int p, int s, int q_f, int i, int l)
{
  int j, k, k_local, q, r;
  jagged1 m_cf_q_r_j, m_cf_r_s_k;
  jagged2 m_cf_r_s;

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
      ++*m_forman_cf_a3_index;
  }
}

/* q_f > 0 => p >= q > r >= s */
static void forman_cf_a3_level_3_nonzero(int * m_forman_cf_a3, int * index,
  const mesh * m, const jagged2 * m_cf_p_s, int p, int m_cn_p, int s, int q_f)
{
  int i, l, l_local;
  int * m_forman_cf_a3_index;
  jagged1 m_cf_p_s_i;

  for (i = 0; i < m_cn_p; ++i)
  {
    jagged2_part1(&m_cf_p_s_i, m_cf_p_s, i);
    for (l_local = 0; l_local < m_cf_p_s_i.a0; ++l_local)
    {
      l = m_cf_p_s_i.a1[l_local];
      m_forman_cf_a3_index = m_forman_cf_a3 + *index;

      /* initialize */
      *m_forman_cf_a3_index = 0;

      /* c(p, i) > c(q, j) > c(r, k) = c(s, l) */
      forman_cf_a3_level_5_nonzero_begin(m_forman_cf_a3_index,
        m, p, s, q_f, i, l);

      /* c(p, i) > c(q, j) > c(r, k) > c(s, l) */
      forman_cf_a3_level_5_nonzero_middle(m_forman_cf_a3_index,
        m, p, s, q_f, i, l);

      /* c(p, i) = c(q, j) > c(r, k) > c(s, l) */
      forman_cf_a3_level_5_nonzero_end(m_forman_cf_a3_index,
        m, p, s, q_f, i, l);

      ++*index;
    }
  }
}

static void forman_cf_a3_dimension_at_most_2(
  int * m_forman_cf_a3, int * index, const int * m_forman_cn)
{
  int m_forman_cn_pf, p_f, q_f, pf_minus_qf, subfaces_total;

  /* all 1-cells are edges, all 2-cells are quadrilaterals */
  for (p_f = 1; p_f <= 2; ++p_f)
  {
    m_forman_cn_pf = m_forman_cn[p_f];
    for (q_f = 0; q_f < p_f; ++q_f)
    {
      pf_minus_qf = p_f - q_f;
      subfaces_total = (1 << pf_minus_qf) * int_binomial(p_f, pf_minus_qf);
      int_array_assign_constant(m_forman_cf_a3 + *index, m_forman_cn_pf,
                                subfaces_total);
      *index += m_forman_cn_pf;
    }
  }
}

static void forman_cf_a3_dimension_at_least_3(
  int * m_forman_cf_a3, int * index, const mesh * m)
{
  int d, m_cn_p, p, p_f, q_f, s;
  int * m_cn;
  jagged2 m_cf_p_s;

  d = m->dim;
  m_cn = m->cn;

  /* in general, higher-order cells may not be quasi-cubes */
  for (p_f = 3; p_f <= d; ++p_f)
  {
    /* q_f = 0 */
    for (p = p_f; p <= d; ++p)
    {
      m_cn_p = m_cn[p];
      s = p - p_f;
      mesh_cf_part2(&m_cf_p_s, m, p, s);
      forman_cf_a3_level_3_zero(m_forman_cf_a3, index,
                                m, &m_cf_p_s, p, m_cn_p, s);
    }
    /* q_f > 0 */
    for (q_f = 1; q_f < p_f; ++q_f)
    {
      for (p = p_f; p <= d; ++p)
      {
        m_cn_p = m_cn[p];
        s = p - p_f;
        mesh_cf_part2(&m_cf_p_s, m, p, s);
        forman_cf_a3_level_3_nonzero(m_forman_cf_a3, index,
                                     m, &m_cf_p_s, p, m_cn_p, s, q_f);
      }
    }
  }
}

void
forman_cf_a3(int * m_forman_cf_a3, const mesh * m, const int * m_forman_cn)
{
  int index = 0;

  /* all 1-cells are edges, all 2-cells are quadrilaterals */
  forman_cf_a3_dimension_at_most_2(m_forman_cf_a3, &index, m_forman_cn);

  /* in general, higher-order cells may not be quasi-cubes */
  forman_cf_a3_dimension_at_least_3(m_forman_cf_a3, &index, m);
}
