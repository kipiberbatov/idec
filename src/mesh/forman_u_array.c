#include <stdlib.h>
#include "forman_private.h"
#include "list.h"

static int * forman_u_array_a1(
  const mesh * m, int m_forman_u_array_a0, int q_f, int p, int i, int q, int j)
{
  int count, j_loc, m_cf_part_a0, r, r_f;
  int * m_cf_part_a1, * m_forman_u_array_a1;
  jagged1 m_cf_part;
  jagged1 m_fc_part;

  m_forman_u_array_a1 = (int *) malloc(m_forman_u_array_a0 * sizeof(int));
  /* NULL pointer check */
  for (r_f = 0; r_f < m_forman_u_array_a0; ++r_f)
  {
    r = q_f + q + r_f;
    mesh_cf_part3(&m_cf_part, m, p, r, i);
    m_cf_part_a0 = m_cf_part.a0;
    m_cf_part_a1 = m_cf_part.a1;
    mesh_fc_part3(&m_fc_part, m, q, r, j);
    count = 0;
    for (j_loc = 0; j_loc < m_cf_part_a0; ++j_loc)
      if (list_member(&m_fc_part, m_cf_part_a1[j_loc]))
        ++count;
    m_forman_u_array_a1[r_f] = count;
  }
  return m_forman_u_array_a1;
}

static int * forman_u_array_a2(
  const mesh * m, int m_forman_u_array_a0, int m_forman_u_array_a2_size,
  int q_f, int p, int i, int q, int j)
{
  int ind, j_loc, m_cf_part_a0, m_cf_part_a1_j_loc, r, r_f;
  int * m_cf_part_a1, * m_forman_u_array_a2;
  jagged1 m_cf_part;
  jagged1 m_fc_part;
  
  m_forman_u_array_a2 = (int *) malloc(m_forman_u_array_a2_size * sizeof(int));
  /* NULL pointer check */
  ind = 0;
  for (r_f = 0; r_f < m_forman_u_array_a0; ++r_f)
  {
    r = q_f + q + r_f;
    mesh_cf_part3(&m_cf_part, m, p, r, i);
    m_cf_part_a0 = m_cf_part.a0;
    m_cf_part_a1 = m_cf_part.a1;
    mesh_fc_part3(&m_fc_part, m, q, r, j);
    for (j_loc = 0; j_loc < m_cf_part_a0; ++j_loc)
    {
      m_cf_part_a1_j_loc = m_cf_part_a1[j_loc];
      if (list_member(&m_fc_part, m_cf_part_a1_j_loc))
      {
        m_forman_u_array_a2[ind] = m_cf_part_a1_j_loc;
        ++ ind;
      }
    }
  }
  return m_forman_u_array_a2;
}

void forman_u_array(jagged2 * m_forman_u_array, const mesh * m,
                    int p_f, int q_f, int p, int i, int q, int j)
{
  int m_forman_u_array_a0, m_forman_u_array_a2_size;
  int * m_forman_u_array_a1, * m_forman_u_array_a2;
  
  m_forman_u_array_a0 = p_f - q_f + 1;
  m_forman_u_array_a1 = 
    forman_u_array_a1(m, m_forman_u_array_a0, q_f, p, i, q, j);
  /* NULL pointer check */
  m_forman_u_array_a2_size = 
    list_sum(m_forman_u_array_a1, 0, m_forman_u_array_a0);
  m_forman_u_array_a2 = 
    forman_u_array_a2(m, m_forman_u_array_a0, m_forman_u_array_a2_size,
                      q_f, p, i, q, j);
  /* NULL pointer check */
  jagged2_set(m_forman_u_array, m_forman_u_array_a0, m_forman_u_array_a1,
              m_forman_u_array_a2);
}
