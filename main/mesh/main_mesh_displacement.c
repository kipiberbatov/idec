#include "double.h"
#include "mesh_qc.h"

static void mesh_displacement_fprint(
  FILE * out, const mesh * m, const cs * m_bd_0, const double * u)
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
    double_fprint_array_raw(out, m_dim_embedded, m_displacement_i);
  }
}

// static void mesh_displacement_fprint_fscan(FILE * out, FILE * in)
// {
//   int m_cn_1;
//   mesh * m;
//   cs ** m_bd;
//   double * u;
//
//   m = mesh_fscan(in);
//   /* NULL pointer check */
//   m_cn_1 = m->cn[1];
//   m_bd = mesh_fscan_bd(in, m);
//   /* NULL pointer check */
//   u = double_fscan_array(in, m_cn_1);
//   /* NULL pointer check */
//   mesh_displacement_fprint(out, m, m_bd[0], u);
//   /* NULL pointer check */
//   free(u);
//   cs_free_array(m_bd, m->dim + 1);
//   mesh_free(m);
// }

static void mesh_displacement_unit_cochain_fprint_fscan(FILE * out, FILE * in)
{
  int i, m_cn_1;
  mesh * m;
  cs ** m_bd;
  double * u;
  
  m = mesh_fscan(in);
  /* NULL pointer check */
  m->fc = mesh_fc(m);
  /* NULL pointer check */
  m_cn_1 = m->cn[1];
  m_bd = mesh_fscan_bd(in, m);
  /* NULL pointer check */
  u = (double *) malloc(m_cn_1 * sizeof(double));
  for (i = 0; i < m_cn_1; ++i)
    u[i] = 1;
  mesh_displacement_fprint(out, m, m_bd[0], u);
  /* NULL pointer check */
  free(u);
  cs_free_array(m_bd, m->dim);
  mesh_free(m);
}

int main()
{
  mesh_displacement_unit_cochain_fprint_fscan(stdout, stdin);
  return 0;
}
