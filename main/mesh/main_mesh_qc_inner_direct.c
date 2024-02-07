#include <errno.h>
#include <stdlib.h>
#include "double.h"
#include "mesh_qc.h"
#include "vector_sparse.h"

static void mesh_qc_inner_direct_fprint_raw(
  FILE * out,
  const mesh_qc * m,
  double ** m_vol
)
{
  int m_dim, p;
  int * m_cn;
  double * m_inner_p;
  
  m_dim = m->dim;
  m_cn = m->cn;
  for (p = 0; p <= m_dim; ++p)
  {
    m_inner_p = mesh_qc_inner_direct_p(m, p, m_vol[p], m_vol[m_dim - p]);
    if (errno)
    {
      fprintf(stderr,
              "mesh_qc_inner_direct_fprint - cannot calculate m_inner[%d]\n", p);
      return;
    }
    
    double_array_fprint(out, m_cn[p], m_inner_p, "--raw");
    if (p != m_dim)
      fputc('\n', out);
    
    free(m_inner_p);
  }
}

int main()
{
  mesh_qc * m;
  matrix_sparse ** m_bd;
  double ** m_vol;
  FILE * in, * out;
  
  out = stdout;
  in = stdin;
  
  m = mesh_fscan(in, "--raw");
  if (errno)
  {
    fputs("main - cannot scan m\n", stderr);
    goto end;
  }
  
  m->fc = mesh_fc(m);
  if (errno)
  {
    fputs("main - cannot calculate m->fc\n", stderr);
    goto m_free;
  }
  
  m_bd = mesh_fscan_bd(in, m);
  if (errno)
  {
    fputs("main - cannot scan m->bd\n", stderr);
    goto m_free;
  }
  
  m_vol = double_array2_fscan(in, m->dim + 1, m->cn, "--raw");
  if (errno)
  {
    fputs("main - cannot scan m_vol\n", stderr);
    goto m_bd_free;
  }
  
  mesh_qc_inner_direct_fprint_raw(out, m, m_vol);
  if (errno)
  {
    fputs("main - cannot print m_inner\n", stderr);
    goto m_vol_free;
  }

m_vol_free:
  double_array2_free(m_vol, m->dim + 1);
m_bd_free:
  matrix_sparse_array_free(m_bd, m->dim);
m_free:
  mesh_free(m);
end:
  return errno;
}
