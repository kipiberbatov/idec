#include "mesh_qc.h"

static void mesh_qc_hodge_coeff_fprint_raw(FILE * out, const mesh * m)
{
  int i, m_dim, p;
  int * m_cn;
  
  m_dim = m->dim;
  m_cn = m->cn;
  for (p = 0; p <= m_dim; ++p)
  {
    for (i = 0; i < m_cn[p] - 1; ++i)
      fprintf(out, "%g ", 1.);
    fprintf(out, "%g\n", 1.);
  }
}

int main()
{
  mesh_qc * m;
  FILE * in, * out;
  
  out = stdout;
  in = stdin;
  m = mesh_fscan(in, "--raw");
  /* NULL pointer and successfull reading check */
  mesh_qc_hodge_coeff_fprint_raw(out, m);
  /* successfull writing check */
  mesh_free(m);
  return 0;
}
