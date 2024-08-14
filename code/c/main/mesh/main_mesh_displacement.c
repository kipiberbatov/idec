#include <stdlib.h>
#include "double.h"
#include "mesh_qc.h"

static void mesh_displacement_file_print_raw(
  FILE * out, const mesh * m, const matrix_sparse * m_bd_0, const double * u)
{
  int i, m_dim_embedded;
  double * m_displacement_i;
  double ** m_displacement;

  m_dim_embedded = m->dim_embedded;
  m_displacement = mesh_displacement(m, m_bd_0, u);
  /* NULL pointer check */
  for (i = 0; i < m->cn[0]; ++i)
  {
    m_displacement_i = m_displacement[i];
    double_array_file_print(out, m_dim_embedded, m_displacement_i, "--raw");
  }
}

static void mesh_displacement_unit_cochain_file_print_file_scan(FILE * out, FILE * in)
{
  int i;
  mesh * m;
  matrix_sparse ** m_bd;
  double * u;

  m = mesh_file_scan(in, "--raw");
  /* NULL pointer check */
  m->fc = mesh_fc(m);
  /* NULL pointer check */
  m_bd = mesh_file_scan_boundary(in, m);
  /* NULL pointer check */
  u = (double *) malloc(sizeof(double) * m->cn[1]);
  for (i = 0; i < m->cn[1]; ++i)
    u[i] = 1;
  // double_array_assign_integer(u, m->cn[1], 1);
  mesh_displacement_file_print_raw(out, m, m_bd[0], u);
  /* NULL pointer check */
  free(u);
  matrix_sparse_array_free(m_bd, m->dim);
  mesh_free(m);
}

int main()
{
  mesh_displacement_unit_cochain_file_print_file_scan(stdout, stdin);
  return 0;
}
