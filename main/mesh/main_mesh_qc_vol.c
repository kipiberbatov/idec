#include <stdlib.h>
#include "double.h"
#include "mesh_qc.h"

static void mesh_qc_vol_file_print_raw(FILE * out, const mesh_qc * m)
{
  int m_dim, p;
  int * m_cn;
  double * m_vol_p;
  
  m_dim = m->dim;
  m_cn = m->cn;
  for(p = 0; p <= m_dim; ++p)
  {
    m_vol_p = mesh_qc_vol_p(m, p);
    /* NULL pointer check */
    double_array_file_print(out, m_cn[p], m_vol_p, "--raw");
    free(m_vol_p);
  }
}

int main()
{
  mesh_qc * m;
  FILE * in, * out;
  
  out = stdout;
  in = stdin;
  m = mesh_file_scan(in, "--raw");
  /* NULL pointer check */
  mesh_qc_vol_file_print_raw(out, m);
  /* NULL pointer check */
  mesh_free(m);
  return 0;
}
