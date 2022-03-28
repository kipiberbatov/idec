#include <errno.h>
#include <stdlib.h>
#include "forman_private.h"
#include "int.h"

static void forman_u_a1(int * m_forman_u_a1, const mesh * m,
                        int p_f, int q_f, int p, int i, int q, int j)
{
  int r, r_f;
  jagged1 m_cf_part;
  jagged1 m_fc_part;

  for (r_f = 0; r_f < p_f - q_f + 1; ++r_f)
  {
    r = q_f + q + r_f;
    mesh_cf_part3(&m_cf_part, m, p, r, i);
    mesh_fc_part3(&m_fc_part, m, q, r, j);
    m_forman_u_a1[r_f] = jagged1_intersection_count(&m_cf_part, &m_fc_part);
  }
}

static void forman_u_a2(int * m_forman_u_a2, const mesh * m,
                        int p_f, int q_f, int p, int i, int q, int j)
{
  int ind, r, r_f;
  jagged1 m_cf_part, m_fc_part, tmp;
  
  ind = 0;
  for (r_f = 0; r_f < p_f - q_f + 1; ++r_f)
  {
    r = q_f + q + r_f;
    mesh_fc_part3(&m_fc_part, m, q, r, j);
    mesh_cf_part3(&m_cf_part, m, p, r, i);
    tmp.a1 = m_forman_u_a2 + ind;
    jagged1_intersection(&tmp, &m_cf_part, &m_fc_part);
    ind += tmp.a0;
  }
}

jagged2 * forman_u(const mesh * m, int p_f, int q_f, int p, int i, int q, int j)
{
  int m_forman_u_a2_size;
  jagged2 * m_forman_u;
  
  m_forman_u = (jagged2 *) malloc(sizeof(jagged2));
  if (errno)
  {
    perror("forman_u - cannot allocate memory for m_forman_u");
    goto end;
  }
  
  m_forman_u->a0 = p_f - q_f + 1;
  m_forman_u->a1 = (int *) malloc(sizeof(int) * m_forman_u->a0);
  if (errno)
  {
    perror("forman_u - cannot allocate memory for m_forman_u->a1");
    goto m_forman_v_free;
  }
  forman_u_a1(m_forman_u->a1, m, p_f, q_f, p, i, q, j);
  
  m_forman_u_a2_size = int_array_total_sum(m_forman_u->a0, m_forman_u->a1);
  m_forman_u->a2 = (int *) malloc(sizeof(int) * m_forman_u_a2_size);
  if (errno)
  {
    perror("forman_u - cannot calculate m_forman_u->a2");
    goto m_forman_v_a1_free;
  }
  forman_u_a2(m_forman_u->a2, m, p_f, q_f, p, i, q, j);
  
  return m_forman_u;
  
  /* cleaning if an error occurs */
m_forman_v_a1_free:
  free(m_forman_u->a1);
m_forman_v_free:
  free(m_forman_u);
end:
  return NULL;
}
