#include "forman_private.h"

void forman_polytope_vertices(
  int * m_forman_cell_to_faces, const mesh * m, const jagged2 * m_forman_u,
  const jagged3 * m_forman_v, const jagged2 * m_forman_fi,
  const jagged3 * m_forman_si, int p_f, int q_f, int q)
{
  int ind, r_f, k_loc, j_loc, r, s, k, l;
  int summand_1, summand_2, l_pos;
  int m_forman_v_a0;
  int * m_forman_v_a1;
  jagged1 face, m_forman_fi_q_f, m_forman_si_r_s, m_forman_u_r_f,
          m_forman_v_r_f_k_loc;
  jagged2 m_forman_v_r_f;
  
  m_forman_v_a0 = m_forman_v->a0;
  m_forman_v_a1 = m_forman_v->a1;
  jagged2_part1(&m_forman_fi_q_f, m_forman_fi, q_f);
  
  ind = 0;
  for (r_f = 0; r_f < m_forman_v_a0; ++r_f)
  {
    jagged2_part1(&m_forman_u_r_f, m_forman_u, r_f);
    jagged3_part1(&m_forman_v_r_f, m_forman_v, r_f);
    r = q_f + q + r_f;
    s = q + r_f;
    summand_1 = jagged1_part1(&m_forman_fi_q_f, s);
    jagged3_part2(&m_forman_si_r_s, m_forman_si, r, s);
    for (k_loc = 0; k_loc < m_forman_v_a1[r_f]; ++k_loc)
    {
      k = jagged1_part1(&m_forman_u_r_f, k_loc);
      jagged2_part1(&m_forman_v_r_f_k_loc, &m_forman_v_r_f, k_loc);
      summand_2 = jagged1_part1(&m_forman_si_r_s, k);
      mesh_cf_part3(&face, m, r, s, k);
      for (j_loc = 0; j_loc < m_forman_v_r_f_k_loc.a0; ++j_loc)
      {
        l = jagged1_part1(&m_forman_v_r_f_k_loc, j_loc);
        l_pos = jagged1_position(&face, l);
        m_forman_cell_to_faces[ind] = summand_1 + summand_2 + l_pos;
        ++ind;
      }
    }
  }
  /* if (p_f == 2 && q_f == 0)
   *   int_swap(&(m_forman_pv[2]), &(m_forman_pv[3]));
   */
}
