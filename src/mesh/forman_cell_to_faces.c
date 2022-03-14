#include <stdlib.h>
#include "forman_private.h"
#include "list.h"

void forman_cell_to_faces(
  int * m_forman_cell_to_faces, const mesh * m, const jagged3 * m_forman_cbi,
  const jagged2 * m_forman_fi, const jagged3 * m_forman_si,
  int p_f, int q_f, int i_f)
{
  int p, i, q, j, m_forman_v_array_a3_size;
  // int form_faces_number;
  jagged1 tmp;
  jagged2 m_forman_u_array;
  jagged3 m_forman_v_array;
  
  jagged3_part2(&tmp, m_forman_cbi, p_f, i_f);
  list_get_4_values(tmp.a1, &p, &i, &q, &j);
  forman_u_array(&m_forman_u_array, m, p_f, q_f, p, i, q, j);
  /* NULL pointer check */
  forman_v_array(&m_forman_v_array, &m_forman_v_array_a3_size,
                 m, &m_forman_u_array, p_f, q_f, q, j);
  /* NULL pointer check */
  forman_polytope_vertices(
    m_forman_cell_to_faces, m, &m_forman_u_array, &m_forman_v_array,
    m_forman_v_array_a3_size, m_forman_fi, m_forman_si, p_f, q_f, q);
  /* NULL pointer check */
  free(m_forman_v_array.a3);
  free(m_forman_v_array.a2);
  free(m_forman_u_array.a2);
  free(m_forman_u_array.a1);
}
