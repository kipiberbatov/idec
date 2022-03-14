#include "double.h"
#include "mesh_qc.h"

static void mesh_qc_vol_fprint(FILE * out, const mesh_qc * m)
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
    double_fprint_array_raw(out, m_cn[p], m_vol_p);
    free(m_vol_p);
  }
}

int main()
{
  mesh_qc * m;
  FILE * in, * out;
  
  out = stdout;
  in = stdin;
  m = mesh_fscan(in);
  /* NULL pointer check */
  mesh_qc_vol_fprint(out, m);
  /* NULL pointer check */
  mesh_free(m);
  return 0;
}
