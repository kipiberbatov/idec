#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "forman_private.h"
#include "int.h"

void forman_cf_a4(int * m_forman_cf_a4, const mesh * m, const int * m_forman_cn)
{
  int ind, i_f, m_dim, m_forman_cn_p_f, p_f, q_f, r_f, vertices_number;
  int m_forman_cell_to_faces[12]; /* 12 = max(vertices_number) */
  jagged2 * m_forman_fi;
  jagged3 * m_forman_cbi, * m_forman_si;

  m_dim = m->dim;
  
  m_forman_cbi = forman_cbi(m, m_forman_cn);
  if (errno)
  {
    perror("forman_cf_a4 - cannot calculate m_forman_cbi");
    goto end;
  }
  
  m_forman_fi = forman_fi(m);
  if (errno)
  {
    perror("forman_cf_a4 - cannot calculate m_forman_fi");
    goto m_forman_cbi_free;
  }
  
  m_forman_si = forman_si(m);
  if (errno)
  {
    perror("forman_cf_a4 - cannot calculate m_forman_si");
    goto m_forman_fi_free;
  }
  
  ind = 0;
  for (p_f = 1; p_f <= m_dim; ++p_f)
  {
    m_forman_cn_p_f = m_forman_cn[p_f];
    for (q_f = 0; q_f < p_f; ++q_f)
    {
      r_f = p_f - q_f;
      vertices_number = (1 << r_f) * int_binomial(p_f, r_f);
      for (i_f = 0; i_f < m_forman_cn_p_f; ++i_f)
      {
        forman_cell_to_faces(m_forman_cell_to_faces, m, m_forman_cbi,
                             m_forman_fi, m_forman_si, p_f, q_f, i_f);
        if (errno)
        {
          perror("forman_cf_a4 - cannot calculate m_forman_cell_to_faces");
          goto m_forman_si_free;
        }
        
        memcpy(m_forman_cf_a4 + ind, m_forman_cell_to_faces,
               sizeof(int) * vertices_number);
        ind += vertices_number;
      }
    }
  }

m_forman_si_free:
  jagged3_free(m_forman_si);
m_forman_fi_free:
  jagged2_free(m_forman_fi);
m_forman_cbi_free:
  jagged3_free(m_forman_cbi);
end:
  return;
}
