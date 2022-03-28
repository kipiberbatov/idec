#include "double.h"
#include "int.h"
#include "mesh_private.h"

void mesh_fprint_raw(FILE * out, const mesh * m)
{
  int /*m_c_size,*/ m_cf_a2_size, m_cf_a3_size, m_cf_a4_size;
  
  fprintf(out, "%d\n", m->dim_embedded);
  
  fprintf(out, "%d\n", m->dim);
  
  int_array_fprint(out, m->dim + 1, m->cn, "--raw");
  
  // m_c_size = int_array_total_sum(m->dim + 1, m->cn);
  // int_array_fprint(out, m_c_size, m->c, "--raw");
  
  m_cf_a2_size = int_array_total_sum(m->dim, m->cf->a1);
  
  m_cf_a3_size = int_array_total_sum(m_cf_a2_size, m->cf->a2);
  int_array_fprint(out, m_cf_a3_size, m->cf->a3, "--raw");
  
  m_cf_a4_size = int_array_total_sum(m_cf_a3_size, m->cf->a3);
  int_array_fprint(out, m_cf_a4_size, m->cf->a4, "--raw");
  
  double_matrix_fprint(out, m->cn[0], m->dim_embedded, m->coord, "--raw");
  /* double_array_fprint(out, m_cn[0] * m_dim_embedded, m_coord, "--raw"); */
}
