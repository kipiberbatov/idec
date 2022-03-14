#include "double.h"
#include "int.h"
#include "list.h"
#include "mesh.h"

void mesh_fprint(FILE * out, const mesh * m)
{
  int m_dim, m_dim_embedded, m_c_size, m_cf_a2_size, m_cf_a3_size, m_cf_a4_size;
  int * m_cn, * m_c, * m_cf_a1, * m_cf_a2, * m_cf_a3, * m_cf_a4;
  double * m_coord;
  jagged4 * m_cf;
  
  m_dim_embedded = m->dim_embedded;
  fprintf(out, "%d\n", m_dim_embedded);
  m_dim = m->dim;
  fprintf(out, "%d\n", m_dim);
  m_cn = m->cn;
  int_fprint_array_raw(out, m_dim + 1, m_cn);
  m_c_size = list_sum(m_cn, 0, m_dim + 1);
  m_c = m->c;
  int_fprint_array_raw(out, m_c_size, m_c);
  m_cf = m->cf;
  m_cf_a1 = m_cf->a1;
  m_cf_a2_size = list_sum(m_cf_a1, 0, m_dim);
  m_cf_a2 = m_cf->a2;
  m_cf_a3_size = list_sum(m_cf_a2, 0, m_cf_a2_size);
  m_cf_a3 = m_cf->a3;
  int_fprint_array_raw(out, m_cf_a3_size, m_cf_a3);
  m_cf_a4_size = list_sum(m_cf_a3, 0, m_cf_a3_size);
  m_cf_a4 = m_cf->a4;
  int_fprint_array_raw(out, m_cf_a4_size, m_cf_a4);
  m_coord = m->coord;
  double_fprint_matrix_raw(out, m_cn[0], m_dim_embedded, m_coord);
  /* double_fprint_array_raw(out, m_cn[0] * m_dim_embedded, m_coord); */
}
