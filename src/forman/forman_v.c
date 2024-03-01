#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "forman_private.h"
#include "int.h"

static void forman_v_a2(
  int * m_forman_v_a2, const mesh * m, int p_f, int q_f, int q, int j,
  const jagged2 * m_forman_u, const int * m_forman_v_a1)
{
  int ind, k, k_loc, r, r_f, s;
  jagged1 m_cf_part, m_fc_part, m_forman_u_r_f;
  
  ind = 0;
  for (r_f = 0; r_f < p_f - q_f + 1; ++r_f)
  {
    r = q + r_f + q_f;
    s = q + r_f;
    mesh_fc_part3(&m_fc_part, m, q, s, j);
    jagged2_part1(&m_forman_u_r_f, m_forman_u, r_f);
    for (k_loc = 0; k_loc < m_forman_v_a1[r_f]; ++k_loc)
    {
      k = jagged1_part1(&m_forman_u_r_f, k_loc);
      mesh_cf_part3(&m_cf_part, m, r, s, k);
      m_forman_v_a2[ind] = jagged1_intersection_count(&m_cf_part, &m_fc_part);
      ++ind;
    }
  }
}

static void forman_v_a3(
  int * m_forman_v_a3, const mesh * m, int p_f, int q_f, int q, int j,
  const jagged2 * m_forman_u, const int * m_forman_v_a1)
{
  int ind, k, k_loc, r, r_f, s;
  jagged1 m_cf_part, m_fc_part, m_forman_u_r_f, tmp;
  
  ind = 0;
  for (r_f = 0; r_f < p_f - q_f + 1; ++r_f)
  {
    r = q + r_f + q_f;
    s = q + r_f;
    mesh_fc_part3(&m_fc_part, m, q, s, j);
    jagged2_part1(&m_forman_u_r_f, m_forman_u, r_f);
    for (k_loc = 0; k_loc < m_forman_v_a1[r_f]; ++k_loc)
    {
      k = jagged1_part1(&m_forman_u_r_f, k_loc);
      mesh_cf_part3(&m_cf_part, m, r, s, k);
      tmp.a1 = m_forman_v_a3 + ind;
      jagged1_intersection(&tmp, &m_cf_part, &m_fc_part);
      ind += tmp.a0;
    }
  }
}

jagged3 * forman_v(
  const mesh * m, const jagged2 * m_forman_u, int p_f, int q_f, int q, int j)
{
  int m_forman_v_a2_size, m_forman_v_a3_size;
  jagged3 * m_forman_v;
  
  m_forman_v = (jagged3 *) malloc(sizeof(jagged3));
  if (errno)
  {
    perror("forman_v - cannot allocate memory for m_forman_v");
    goto end;
  }
  
  m_forman_v->a0 = m_forman_u->a0;
  m_forman_v->a1 = (int *) malloc(sizeof(int) * m_forman_v->a0);
  if (errno)
  {
    perror("forman_v - cannot allocate memory for m_forman_v->a1");
    goto m_forman_v_free;
  }
  memcpy(m_forman_v->a1, m_forman_u->a1, sizeof(int) * m_forman_v->a0);
  
  m_forman_v_a2_size = int_array_total_sum(m_forman_v->a0, m_forman_v->a1);
  m_forman_v->a2 = (int *) malloc(sizeof(int) * m_forman_v_a2_size);
  if (errno)
  {
    perror("forman_v - cannot allocate memory for m_forman_v->a2");
    goto m_forman_v_a1_free;
  }
  forman_v_a2(m_forman_v->a2, m, p_f, q_f, q, j, m_forman_u, m_forman_v->a1);
  
  m_forman_v_a3_size = int_array_total_sum(m_forman_v_a2_size, m_forman_v->a2);
  m_forman_v->a3 = (int *) malloc(sizeof(int) * m_forman_v_a3_size);
  if (errno)
  {
    perror("forman_v - cannot allocate memory for m_forman_v->a3");
    goto m_forman_v_a2_free;
  }
  forman_v_a3(m_forman_v->a3, m, p_f, q_f, q, j, m_forman_u, m_forman_v->a1);
  
  return m_forman_v;
  
  /* cleaning if an error occurs */
m_forman_v_a2_free:
  free(m_forman_v->a2);
m_forman_v_a1_free:
  free(m_forman_v->a1);
m_forman_v_free:
  free(m_forman_v);
end:
  return NULL;
}
