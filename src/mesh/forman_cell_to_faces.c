#include <errno.h>
#include <stdlib.h>
#include "forman_private.h"
#include "int.h"

void forman_cell_to_faces(
  int * m_forman_cell_to_faces, const mesh * m, const jagged3 * m_forman_cbi,
  const jagged2 * m_forman_fi, const jagged3 * m_forman_si,
  int p_f, int q_f, int i_f)
{
  int p, i, q, j;
  jagged1 tmp;
  jagged2 * m_forman_u;
  jagged3 * m_forman_v;
  
  jagged3_part2(&tmp, m_forman_cbi, p_f, i_f);
  int_array_4_values_get(tmp.a1, &p, &i, &q, &j);
  
  m_forman_u = forman_u(m, p_f, q_f, p, i, q, j);
  if (errno)
  {
    perror("forman_cell_to_faces - cannot calculate m_forman_u");
    goto end;
  }
  
  m_forman_v = forman_v(m, m_forman_u, p_f, q_f, q, j);
  if (errno)
  {
    perror("forman_cell_to_faces - cannot calculate m_forman_v");
    goto m_forman_u_free;
  }
  
  forman_polytope_vertices(m_forman_cell_to_faces, m, m_forman_u, m_forman_v,
                           m_forman_fi, m_forman_si, p_f, q_f, q);
  
  jagged3_free(m_forman_v);
m_forman_u_free:
  jagged2_free(m_forman_u);
end:
  return;
}
