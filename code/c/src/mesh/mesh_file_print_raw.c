#include "double_matrix.h"
#include "int.h"
#include "mesh_private.h"

void mesh_file_print_raw(FILE * out, const mesh * m)
{
  int m_cf_a2_size, m_cf_a3_size, m_cf_a4_size;

  fprintf(out, "%d\n", m->dim_embedded);

  fprintf(out, "%d\n", m->dim);

  int_array_file_print(out, m->dim + 1, m->cn, "--raw");

  m_cf_a2_size = int_array_total_sum(m->dim, m->cf->a1);

  m_cf_a3_size = int_array_total_sum(m_cf_a2_size, m->cf->a2);
  int_array_file_print(out, m_cf_a3_size, m->cf->a3, "--raw");

  m_cf_a4_size = int_array_total_sum(m_cf_a3_size, m->cf->a3);
  int_array_file_print(out, m_cf_a4_size, m->cf->a4, "--raw");

  double_matrix_file_print(out, m->cn[0], m->dim_embedded, m->coord, "--raw");
}
