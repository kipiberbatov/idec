#include "forman_private.h"
// #include "imath.h"
#include "list.h"

void forman_polytope_vertices(
  int * m_forman_pv, const mesh * m, const jagged2 * m_forman_u_array,
  const jagged3 * m_forman_v_array, int m_forman_v_array_a3_size,
  const jagged2 * m_forman_fi, const jagged3 * m_forman_si,
  int p_f, int q_f, int q)
{
  int ind, r_f, k_loc, j_loc, r, s, k, l;
  int summand_1, summand_2, l_pos;
  int m_forman_v_array_a0;
  int * m_forman_v_array_a1;
  jagged1 face, m_forman_v_array_a2_ind;
  
  m_forman_v_array_a0 = m_forman_v_array->a0;
  m_forman_v_array_a1 = m_forman_v_array->a1;
  ind = 0;
  for (r_f = 0; r_f < m_forman_v_array_a0; ++r_f)
  {
    r = q_f + q + r_f;
    s = q + r_f;
    summand_1 = jagged2_part2(m_forman_fi, q_f, s);
    for (k_loc = 0; k_loc < m_forman_v_array_a1[r_f]; ++k_loc)
    {
      k = jagged2_part2(m_forman_u_array, r_f, k_loc);
      jagged3_part2(&m_forman_v_array_a2_ind, m_forman_v_array, r_f, k_loc);
      summand_2 = jagged3_part3(m_forman_si, r, s, k);
      mesh_cf_part3(&face, m, r, s, k);
      for (j_loc = 0; j_loc < m_forman_v_array_a2_ind.a0; ++j_loc)
      {
        l = jagged3_part3(m_forman_v_array, r_f, k_loc, j_loc);
        l_pos = list_position(&face, l);
        m_forman_pv[ind] = summand_1 + summand_2 + l_pos;
        ++ind;
      }
    }
  }
  // if (p_f == 2 && q_f == 0)
  //   imath_swap(&(m_forman_pv[2]), &(m_forman_pv[3]));
}
