#include <stdlib.h>
#include "forman_private.h"
#include "list.h"

static int * forman_v_array_a2(
  const mesh * m, int m_forman_v_array_a2_size, int p_f, int q_f, int q, int j,
  const jagged2 * m_forman_u_array, const int * m_forman_v_array_a1)
{
  int count, ind, j_loc, k, k_loc, m_cf_part_a0, r, r_f, s;
  int * m_cf_part_a1, * m_forman_v_array_a2;
  jagged1 m_cf_part, m_fc_part, tmp;
  
  m_forman_v_array_a2 = (int *) malloc(m_forman_v_array_a2_size * sizeof(int));
  /* NULL pointer check */
  ind = 0;
  for (r_f = 0; r_f < p_f - q_f + 1; ++r_f)
  {
    r = q_f + q + r_f;
    s = q + r_f;
    mesh_fc_part3(&m_fc_part, m, q, s, j);
    jagged2_part1(&tmp, m_forman_u_array, r_f);
    for (k_loc = 0; k_loc < m_forman_v_array_a1[r_f]; ++k_loc)
    {
      k = jagged1_part1(&tmp, k_loc);
      mesh_cf_part3(&m_cf_part, m, r, s, k);
      m_cf_part_a0 = m_cf_part.a0;
      m_cf_part_a1 = m_cf_part.a1;
      count = 0;
      for (j_loc = 0; j_loc < m_cf_part_a0; ++j_loc)
        if (list_member(&m_fc_part, m_cf_part_a1[j_loc]))
          ++count;
      m_forman_v_array_a2[ind] = count;
      ++ind;
    }
  }
  return m_forman_v_array_a2;
}

static int * forman_v_array_a3(
  const mesh * m, int m_forman_v_array_a3_size, int p_f, int q_f, int q, int j,
  const jagged2 * m_forman_u_array, const int * m_forman_v_array_a1)
{
  int count, ind, j_loc, k, k_loc, m_cf_part_a0, m_cf_part_a1_j_loc, r, r_f, s;
  int * m_cf_part_a1, * m_forman_v_array_a3;
  jagged1 m_cf_part, m_fc_part, tmp;
  
  m_forman_v_array_a3 = (int *) malloc(m_forman_v_array_a3_size * sizeof(int));
  /* NULL pointer check */
  ind = 0;
  for (r_f = 0; r_f < p_f - q_f + 1; ++r_f)
  {
    r = q_f + q + r_f;
    s = q + r_f;
    mesh_fc_part3(&m_fc_part, m, q, s, j);
    jagged2_part1(&tmp, m_forman_u_array, r_f);
    for (k_loc = 0; k_loc < m_forman_v_array_a1[r_f]; ++k_loc)
    {
      k = jagged1_part1(&tmp, k_loc);
      mesh_cf_part3(&m_cf_part, m, r, s, k);
      m_cf_part_a0 = m_cf_part.a0;
      m_cf_part_a1 = m_cf_part.a1;
      count = 0;
      for (j_loc = 0; j_loc < m_cf_part_a0; ++j_loc)
      {
        m_cf_part_a1_j_loc = m_cf_part_a1[j_loc];
        if (list_member(&m_fc_part, m_cf_part_a1_j_loc))
        {
          m_forman_v_array_a3[ind] = m_cf_part_a1_j_loc;
          ++ind;
        }
      }
    }
  }
  return m_forman_v_array_a3;
}

void forman_v_array(jagged3 * m_forman_v_array, int * m_forman_v_array_a3_size,
                    const mesh * m, const jagged2 * m_forman_u_array,
                    int p_f, int q_f, int q, int j)
{
  int m_forman_v_array_a0, m_forman_v_array_a2_size;
  int * m_forman_v_array_a1, * m_forman_v_array_a2, * m_forman_v_array_a3;
  
  m_forman_v_array_a0 = m_forman_u_array->a0;
  m_forman_v_array_a1 = m_forman_u_array->a1;
  m_forman_v_array_a2_size =
    list_sum(m_forman_v_array_a1, 0, m_forman_v_array_a0);
  m_forman_v_array_a2 = 
    forman_v_array_a2(m, m_forman_v_array_a2_size, p_f, q_f, q, j,
                      m_forman_u_array, m_forman_v_array_a1);
 /* NULL pointer check */
 *m_forman_v_array_a3_size =
   list_sum(m_forman_v_array_a2, 0, m_forman_v_array_a2_size);
 m_forman_v_array_a3 = 
   forman_v_array_a3(m, *m_forman_v_array_a3_size, p_f, q_f, q, j,
                     m_forman_u_array, m_forman_v_array_a1);
  /* NULL pointer check */
  jagged3_set(m_forman_v_array, m_forman_v_array_a0, m_forman_v_array_a1,
              m_forman_v_array_a2, m_forman_v_array_a3);
}
