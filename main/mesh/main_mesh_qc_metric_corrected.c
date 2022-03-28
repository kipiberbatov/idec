#include <errno.h>
#include <stdlib.h>
#include "double.h"
#include "mesh_qc.h"

static void mesh_qc_metric_corrected_fprint_only_values(
  FILE * out, const mesh_qc * m, double ** m_vol, double * node_curvatures)
{
  int m_dim, p;
  int * m_cn;
  vector_sparse ** m_metric_p;
  
  m_dim = m->dim;
  m_cn = m->cn;
  
  for (p = 0; p <= m_dim; ++p)
  {
    m_metric_p = mesh_qc_metric_corrected_p(m, p, m_vol[p], node_curvatures);
    if (errno)
    {
      fprintf(stderr, "mesh_qc_metric_corrected_fprint - cannot calculate "
              "m_metric[%d]\n", p);
      return;
    }
    
    vector_sparse_array_fprint(out, m_cn[p], m_metric_p, "--only-values");
    if (p != m_dim)
      fputc('\n', out);
    vector_sparse_array_free(m_metric_p, m_cn[p]);
  }
}

int main()
{
  int m_dim;
  int * m_cn;
  mesh_qc * m;
  matrix_sparse ** m_bd;
  double * node_curvatures;
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
  
  m_dim = m->dim;
  m_cn = m->cn;
  
  m_bd = mesh_fscan_bd(in, m);
  if (errno)
  {
    fputs("main - cannot scan m_bd\n", stderr);
    goto m_free;
  }
  
  m_vol = double_array2_fscan(in, m_dim + 1, m_cn, "--raw");
  if (errno)
  {
    fputs("main - cannot scan m_vol\n", stderr);
    goto m_bd_free;
  }
  
  node_curvatures = double_array_fscan(in, m_cn[0], "--raw");
  if (errno)
  {
    fputs("main - cannot scan node_curvature\n", stderr);
    goto m_vol_free;
  }
  
  mesh_qc_metric_corrected_fprint_only_values(out, m, m_vol, node_curvatures);
  if (errno)
  {
    fputs("main - cannot print m_metric\n", stderr);
    goto node_curvatures_free;
  }

node_curvatures_free:
  free(node_curvatures);
m_vol_free:
  double_array2_free(m_vol, m_dim + 1);
m_bd_free:
  matrix_sparse_array_free(m_bd, m_dim);
m_free:
  mesh_free(m);
end:
  return errno;
}
