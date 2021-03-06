#include <stdlib.h>
#include "double.h"
#include "mesh_qc.h"

static void mesh_displacement_fprint_raw(
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
    double_array_fprint(out, m_dim_embedded, m_displacement_i, "--raw");
  }
}

static void mesh_displacement_unit_cochain_fprint_fscan(FILE * out, FILE * in)
{
  int i;
  mesh * m;
  matrix_sparse ** m_bd;
  double * u;
  
  m = mesh_fscan(in, "--raw");
  /* NULL pointer check */
  m->fc = mesh_fc(m);
  /* NULL pointer check */
  m_bd = mesh_fscan_bd(in, m);
  /* NULL pointer check */
  u = (double *) malloc(sizeof(double) * m->cn[1]);
  for (i = 0; i < m->cn[1]; ++i)
    u[i] = 1;
  // double_array_assign_integer(u, m->cn[1], 1);
  mesh_displacement_fprint_raw(out, m, m_bd[0], u);
  /* NULL pointer check */
  free(u);
  matrix_sparse_array_free(m_bd, m->dim);
  mesh_free(m);
}

int main()
{
  mesh_displacement_unit_cochain_fprint_fscan(stdout, stdin);
  return 0;
}
